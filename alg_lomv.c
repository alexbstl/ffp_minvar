#include "alg_lomv.h"

int add(int a, int b)
{
    return a + b;
}


double linf(int row, int col, gsl_matrix * a, gsl_matrix * b){
    assert(row ==1 || col == 1);
    double max = 0;
    if(row == 1){
        for(int i=0; i<col; i++){
            double diff = fabs(gsl_matrix_get(a, 0, i) - gsl_matrix_get(b, 0, i));
            if (diff > max){
                max = diff;
            }
        }
    }
    else if(col == 1){
        for(int i=0; i<row; i++){
            double diff = fabs(gsl_matrix_get(a, i, 0) - gsl_matrix_get(b, i, 0));
            if (diff > max){
                max = diff;
            }
        }
    }
    
    return max;
}


// Slides 16  "Define psi." Name declaration slightly different.
/* 21. 
    def psi(theta):
    chi = Dinv * (ones >= B @ theta)
    b = B.T @ chi  # q-1
    A = Vinv + (B.T @ np.diag(chi)) @ B
    return solve(A,b)
*/
// p-q : 500-4 from .py
// theta: q-1, 4-1
// B: p-q, 500-4
// V: q-q, 4-4
// Delta: p-p, 500-500  
// return: q-1, 4-1

// ** use unsigned int (x)
// ** pass in delta as vector of all diagnoals. Saved memory.
gsl_vector * psi(int p, int q, gsl_vector * theta, gsl_matrix * B, gsl_matrix * V, gsl_vector * Delta){
    gsl_vector *  B_theta = gsl_vector_alloc(p);
    gsl_vector * comparison = gsl_vector_alloc(p);
    gsl_vector * chi = gsl_vector_alloc(p);
    gsl_vector * b = gsl_vector_alloc(q);;

    // B_theta: B @ theta
    // p-1
    gsl_blas_dgemv(CblasNoTrans, 1.0, B, theta, 0.0, B_theta);

    // comparison: ones >= B @ theta
    // p-1
    for(int i=0; i<p; i++){
        double value = (250 >= gsl_vector_get(B_theta, i)) ? 1.0:0.0; // change to 1.0 for formal use
        gsl_vector_set(comparison, i, value);
    }

    // D is diagonal, so Dinv is just 1/diag
    gsl_matrix * Dinv = gsl_matrix_alloc(p, p);
    gsl_matrix_set_zero(Dinv);
    for(int i=0; i<p; i++){
        double diag_inv = 1/gsl_vector_get(Delta, i);
        gsl_matrix_set(Dinv, i, i, diag_inv);
    }

    // chi = Dinv * (ones >= B @ theta)
    // p-1
    gsl_blas_dgemv(CblasNoTrans, 1.0, Dinv, comparison, 0.0, chi);

    // b = B.T @ chi
    // q-1
    gsl_blas_dgemv(CblasTrans, 1.0, B, chi, 0.0, b);

    // A = Vinv + (B.T @ np.diag(chi)) @ B
    // V memory will be modified by the gsl_linalg_LU_decomp. 
    int s;
    gsl_permutation * perm = gsl_permutation_alloc(q);
    gsl_matrix * Vinv = gsl_matrix_alloc(q, q);
    gsl_linalg_LU_decomp(V, perm, &s);
    gsl_linalg_LU_invert(V, perm, Vinv);

    // B.T @ np.diag(chi)
    gsl_matrix * temp1 = gsl_matrix_alloc(q, p);
    gsl_matrix * chi_D = gsl_matrix_alloc(p, p);
    gsl_matrix_set_zero(chi_D);
    for(int i=0; i<p; i++){
        gsl_matrix_set(chi_D, i, i, gsl_vector_get(chi, i));
    }
    gsl_blas_dgemm(CblasTrans, CblasNoTrans, 1.0, B, chi_D, 0.0, temp1);

    // ~ @ B
    gsl_matrix * temp2 = gsl_matrix_alloc(q, q);
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, temp1, B, 0.0, temp2);
    
    //gsl_matrix_fprintf(stdout, temp1, "%g");
    gsl_matrix_fprintf(stdout, temp2, "%g");
    printf("-------------------\n");

    // the sum will be stored in Vinv. A is in fact Vinv.
    gsl_matrix_add(Vinv, temp2);

    // Use gsl_linalg_lU_decomp + gsl_linalg_lu_solve. (BLAS gsl_blas_dtrsv?)
    gsl_vector * x = gsl_vector_alloc(q);
    gsl_linalg_LU_decomp(Vinv, perm, &s);
    gsl_linalg_LU_solve(Vinv, perm, b, x);

    //free all created matrices and vectors
    gsl_vector_free(B_theta);
    gsl_vector_free(comparison);
    gsl_vector_free(chi);
    gsl_vector_free(b);
    gsl_matrix_free(Dinv);
    gsl_permutation_free(perm);
    gsl_matrix_free(Vinv);
    gsl_matrix_free(temp1);
    gsl_matrix_free(chi_D);
    gsl_matrix_free(temp2);

    return x;
}


/* 22.
    def compute_fixed_point (t):
        s = t + 2 * tol
        while (norm(s - t) > tol * norm(s)):
            t = s
            s = psi(t)

        return(s)
*/
/*
// 1. An ffp function that only returns theta so far. 
//    or actually, not returning anything...
// theta: q-1
// B: p-q
// V: q-q
// Delta: p-p
// return: q-1
double** ffp(int p, int q, double** theta, double** B, double** V, double** Delta){
    //  th_old = t0 - np.inf
    double** th_old = mat_zeros(q,1);
    for(int i=0; i<q;i++){
        th_old[i][0] = theta[i][0] - INFINITY;
    } 

    //  th_new = t0
    double** th_new = mat_zeros(q,1);
    copy_mat(q,1, th_new, theta);

    while(linf(q, 1, th_new, th_old) > pow(10, -15)){
        // free space before assign new values
        double** temp = th_old;
        free_ptr(q, temp);
        // th_old = th_new
        th_old = th_new;
        // th_new = psi(th_old)
        // ** memory issue ****
        // ** Just pass in th_new to psi. Work on the th_new memory from psi. No need to return double pointer.
        th_new = psi(p ,q, th_old, B, V, Delta);
    }
    

    free_ptr(q, th_old);
    return th_new;
}


// Slides 11 eq. For verifying theorem1.
/* 23. 
    def lo_weights ():
        theta = psi (np.zeros(q))
        // w is a fixed point of psi, i.e., w = psi(w)
        w = Dinv @ maximum(ones - B @ theta, 0)

        // unique solution x = w/<w, e>
        return w / sum(w)
*/
/* INPUT: 
   OUTPUT: w/sum(w). p-1
   x: p-1
   B: p-q
   V: q-q
   Delta: p-p
*/
/*
double** lo_minvar(int p, int q, double** B, double** V, double** Delta){
    // theta = psi (np.zeros(q))
    double** zeros = mat_zeros(q, 1);
    double** theta = ffp(p, q, zeros, B, V, Delta);
    // w = Dinv @ maximum(ones - B @ theta, 0)
    // B @ theta
    double** B_Theta = mat_mul(p, q, 1,  B, theta);
    // maximum(ones - B @ theta, 0)
    double** comparison = mat_zeros(p,1);
    for(int i=0; i<p; i++){
        comparison[i][0] = 1>B_Theta[i][0] ? 1-B_Theta[i][0]:0 ;
    }
    // w = Dinv @ maximum
    double** Dinv = inv(p, Delta);
    double** w = mat_mul(p,p,1, Dinv, comparison);
    // sum(w)
    double sum = 0;
    for(int i=0; i<p; i++){
        sum += w[i][0];
    }
    // return w / sum(w)
    for(int i=0; i<p; i++){
        w[i][0] = w[i][0] / sum;
    }

    // free space
    free_ptr(q, zeros);
    free_ptr(q, theta);
    free_ptr(p, B_Theta);
    free_ptr(p, comparison);
    free_ptr(p, Dinv);

    return w;
}





/* 
phi(theta) = V @ B.T @ Dinv @ maximum(ones - B @ theta, 0)      //slides 11
psi(theta) = Ainv @ b                                           //slides 16    

*/