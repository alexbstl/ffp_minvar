#include "alg_lomv.h"


double linf(int length, double a[1][length], double b[1][length]){
    double max = 0;
    for(int i=0; i<length; i++){
        if (fabs(a[0][i] - b[0][i]) > max){
            max = fabs(a[0][i] - b[0][i]);
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
void psi(int p, int q, double x[q][1], double theta[q][1], double B[p][q], double V[q][q], double Delta[p][p]){
    double chi[p][1];
    double B_times_theta[p][1];
    double comparison[p][1];
    double b[q][1];
    //B @ theta
    mat_mul(p, q, 1, B_times_theta, B, theta);
    inverse(p, Delta);
    // ones >= B @ theta
    for(int i=0; i<p; i++){
        comparison[i][0] = (1>=B_times_theta[i][0])? 1:0 ;
    }
    // chi = Dinv * (ones >= B @ theta)
    mat_mul(p,p,1, chi, Delta, comparison);
    // b = B.T @ chi
    double B_T[q][p];
    mat_trans(p,q, B, B_T);
    mat_mul(q,p,1, b, B_T, chi);
    // A = Vinv + (B.T @ np.diag(chi)) @ B
    inverse(q, V);
    double chi_diag[p][p];
    mat_diag(p, chi, chi_diag);
    double M1[q][p], M2[q][q];
    mat_mul(q,p,p, M1, B_T, chi_diag);
    mat_mul(q,p,q, M2, M1, B);
    double A[q][q];
    mat_add(q, q, A, V, M2);
    // solve(A,b) by A^-1 * b
    inverse(q, A);
    mat_mul(q,q,1, x, A, b);    
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
// 2. x[q][1] is the array that we want. 
void ffp(int p, int q, double x[q][1], double theta[q][1], double B[p][q], double V[q][q], double Delta[p][p]){
    double th_old[q][1];
    for(int i=0; i<q;i++){
        th_old[i][0] = theta[i][0] - INFINITY;
    } 
    double th_new[q][1];
    memcpy(th_new, theta, sizeof(th_new));
    while(linf(q, th_new, th_old) > pow(10, -15)){
        // th_old = th_new
        memcpy(th_old, th_new, sizeof(th_old));
        // th_new = psi(th_old)
        psi(p,q,th_new, th_old, B, V, Delta);
    }

    memcpy(x, th_new, sizeof(x));
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
void lo_minvar(int p, int q, double x[p][1], double B[p][q], double V[q][q], double Delta[p][p]){
    double theta[q][1];
    double zeros[q][1];
    mat_zeros(q,1, zeros);
    // theta = psi (np.zeros(q))
    ffp(p,q,theta, zeros, B, V, Delta);
    // w = Dinv @ maximum(ones - B @ theta, 0)
    inverse(p, Delta);
    // @
    double B_times_theta[p][1];
    mat_mul(p,q,1, B_times_theta, B, theta);
    // maximum
    double comparison[p][1];
    for(int i=0; i<p; i++){
        comparison[i][0] = 1>B_times_theta[i][0] ? 1-B_times_theta[i][0]:0 ;
    }
    // w
    double w[p][1];
    mat_mul(p,p,1, w, Delta, comparison);
    //
    double sum = 0;
    for(int i=0; i<p; i++){
        sum += w[i][0];
    }
    for(int i=0; i<p; i++){
        w[i][0] = w[i][0] / sum;
    }
    memcpy(x, w, sizeof(w));
}





/* 
phi(theta) = V @ B.T @ Dinv @ maximum(ones - B @ theta, 0)      //slides 11
psi(theta) = Ainv @ b                                           //slides 16    

*/