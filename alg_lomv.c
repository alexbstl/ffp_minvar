#include "alg_lomv.h"
#include "assert.h"
int add(int a, int b)
{
    return a + b;
}

double test(double** a, double** b){
    return a[1][3] + b[2][2] ;
}

double linf(int row, int col, double** a, double** b){
    assert(row ==1 || col == 1);
    double max = 0;
    if(row == 1){
        for(int i=0; i<col; i++){
            if (fabs(a[0][i] - b[0][i]) > max){
                max = fabs(a[0][i] - b[0][i]);
            }
        }
    }
    else if(col == 1){
        for(int i=0; i<row; i++){
            if (fabs(a[i][0] - b[i][0]) > max){
                max = fabs(a[i][0] - b[i][0]);
            }
        }
    }
    
    return max;
}


// Slides 16  "Define psi." Name declaration slightly different.
/* 21. 
    def psi(theta):
    chi = Dinv * (ones >= B @ theta)
    b = B.T @ chi
    A = Vinv + (B.T @ np.diag(chi)) @ B
    return solve(A,b)
*/
// theta: q-1
// B: p-q
// V: q-q
// Delta: p-p
// returm: q-1
double** psi(int p, int q, double** theta, double** B, double** V, double** Delta){
    double** chi;
    double** B_theta;
    double** ones = mat_ones(p,1);
    double** comparison = mat_zeros(p,1);
    double** B_T;
    double** b;
    double** A;

    // B @ theta
    // p-1
    B_theta = mat_mul(p, q, 1, B, theta);

    // ones >= B @ theta
    for(int i=0; i<p; i++){
        comparison[i][0] = (1>=B_theta[i][0])? 1:0 ;
    }

    // chi = Dinv * (ones >= B @ theta)
    // p-1
    chi = mat_mul(p, p, 1, inverse(p, Delta), comparison);

    // B.T
    // q-p
    B_T = mat_trans(p, q, B);

    // b = B.T @ chi
    // q-1
    b = mat_mul(q, p, 1, B_T, chi);

    // A = Vinv + (B.T @ np.diag(chi)) @ B
    // q-q
    double**m1 = mat_mul(q, p, p, B_T, mat_diag(p, mat_trans(p,1, chi)));
    double**m2 = mat_mul(q,p,q, m1, B);
    A = mat_add(q, q, inverse(q, V), m2); 

    // solve(A,b) by A^-1 * b
    return mat_mul(q, q, 1, inverse(q, A), b);
}


/* 22.
    def compute_fixed_point (t):
        s = t + 2 * tol
        while (norm(s - t) > tol * norm(s)):
            t = s
            s = psi(t)

        return(s)
*/

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
    double** th_new = theta;

    while(linf(q, 1, th_new, th_old) > pow(10, -15)){
        // th_old = th_new
        th_old = th_new;
        // th_new = psi(th_old)
        th_new = psi(p ,q, th_old, B, V, Delta);
    }

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
double** lo_minvar(int p, int q, double** B, double** V, double** Delta){
    // theta = psi (np.zeros(q))
    double** theta = ffp(p, q, mat_zeros(q, 1), B, V, Delta);
    // w = Dinv @ maximum(ones - B @ theta, 0)
    // B @ theta
    double** B_Theta = mat_mul(p, q, 1,  B, theta);
    // maximum(ones - B @ theta, 0)
    double** comparison = mat_zeros(p,1);
    for(int i=0; i<p; i++){
        comparison[i][0] = 1>B_Theta[i][0] ? 1-B_Theta[i][0]:0 ;
    }
    // w = Dinv @ maximum
    double** w = mat_mul(p,p,1, inverse(p, Delta), comparison);
    // sum(w)
    double sum = 0;
    for(int i=0; i<p; i++){
        sum += w[i][0];
    }
    // return w / sum(w)
    for(int i=0; i<p; i++){
        w[i][0] = w[i][0] / sum;
    }

    return w;
}





/* 
phi(theta) = V @ B.T @ Dinv @ maximum(ones - B @ theta, 0)      //slides 11
psi(theta) = Ainv @ b                                           //slides 16    

*/