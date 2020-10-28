#include "mat_ops.h"

// Initialize global seed used for xorshift96
static uint32_t seed = 1;

// Convenient ways. Not recommended. 
int easy_rand(int min, int max){
    srand(time(0));
    return rand() % (max + 1 - min) + min;
}

/*  Modified Marsaglia's xorshift random number generator:
    http://www.jstatsoft.org/v08/i14/paper
    Great algorithm. Return pseudo random uint32_t number with longer period of 2^96-1
*/
void s_xorshift96(uint32_t usr_def_seed){
    seed = usr_def_seed;
}


uint32_t xorshift96(int min, int max){
	uint32_t reg_y = seed << 1, reg_z = 521288629;
	uint32_t reg_t = (seed ^ (seed << 10)); 
    seed = reg_y; 
    reg_y = reg_z; 
    reg_z = (reg_z^(reg_z>>26))^(reg_t ^ (reg_t >> 5));
    return reg_z % (max + 1 - min) + min;
}


// Create Matrix of Zeros
void mat_zeros(int rows, int cols, double mat[rows][cols]){
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            mat[i][j]=0;
        }
    }
}


// Create Matrix of Ones
void mat_ones(int rows, int cols, double mat[rows][cols]){
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++)
            mat[i][j]=1;
    }
}


// Matrix Multiplication
void mat_mul(int m, int p, int n, double product[m][n], double mat_l[m][p], double mat_r[p][n]) {
    // Require: mat_l is m x p and mat_r is p x n.
    int i, j, k;
    // matrix multiplication
    for (i = 0; i < m; i++ )
        for (j = 0; j < n; j++ )
            for (k = 0; k < p; k++ )
                product[i][j] = mat_l[i][k] * mat_r[k][j];
}


// Matrix Transpose
void mat_trans(int rows, int cols, double mat_old[rows][cols], double mat_new[cols][rows]){
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            mat_new[j][i] = mat_old[i][j];
        }
    }
}


// Construct diagonal matrix from vector
void mat_diag(int length, double vec[length][1], double mat[length][length]){
    mat_zeros(length, length, mat);
    for(int i=0; i<length; i++){           
        mat[i][i] = vec[i][0];
    }
}


void mat_add(int m, int n, double result[m][n], double mat1[m][n], double mat2[m][n]){
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}


/*For calculating Determinant of the Matrix */
double determinant(int init_k, int order, double a[init_k][init_k])
{
    double s = 1, det = 0, b[init_k][init_k];
    int i, j, m, n, c;
    if (order == 1)
        {
        return (a[0][0]);
        }
    else
        {
        det = 0;
        for (c = 0; c < order; c++)
        {
            m = 0;
            n = 0;
            for (i = 0;i < order; i++)
            {
                for (j = 0 ;j < order; j++)
                {
                    b[i][j] = 0;
                    if (i != 0 && j != c)
                    {
                    b[m][n] = a[i][j];
                    if (n < (order - 2))
                        n++;
                    else
                        {
                        n = 0;
                        m++;
                        }
                    }
                }
            }
            det = det + s * (a[0][c] * determinant(init_k, order - 1, b));
            s = -1 * s;
        }
    }
    return (det);
}

// Default requirement: num is squre.
void inverse(int f, double num[f][f])
{
    double det = determinant(f,f, num);
    if(det == 0.0){
        printf("Inverse of this matrix is impossible!\n");
    }
    else{
        double b[f][f], fac[f][f];
        int p, q, m, n, i, j;
        for (q = 0;q < f; q++){
            for (p = 0;p < f; p++){
                m = 0;
                n = 0;
                for (i = 0;i < f; i++){
                    for (j = 0;j < f; j++){
                        if (i != q && j != p){
                            b[m][n] = num[i][j];
                            if (n < (f - 2))
                                n++;
                            else{
                                n = 0;
                                m++;
                            }
                        }
                    }
                }
                // Find the cofactor matrix and after dividing each entry with its determinant
                fac[q][p] = pow((double)-1, (double) (q + p)) * determinant(f, f - 1, b);
            }
        }

        mat_trans(f,f, fac, num);

        for(int i=0; i<f; i++){
            for(int j=0; j<f; j++){
                num[i][j] = num[i][j]/det;
            }
        }
    }
}