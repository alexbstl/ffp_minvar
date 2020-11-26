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

// - initialize array pointer: allocate memory. 
// - value automatically 00.0
double* init_arr(int length){
    double* arr = (double*) malloc(length * sizeof(double));
    for(int i=0; i<length; i++){
        arr[i] = 0.0;
    }
    return arr;
}

// Create Matrix of Zeros
double** mat_zeros(int row, int col){
    double **mat = (double **)malloc(row * sizeof(double*));
    for (int i=0; i<row; i++) 
         mat[i] = (double *)malloc(col * sizeof(double)); 
    return mat;
}


// Create Matrix of Ones
double** mat_ones(int row, int col){
    double **mat = (double **)malloc(row * sizeof(double*));
    for (int i=0; i<row; i++) 
         mat[i] = (double *)malloc(col * sizeof(double)); 
    for (int i=0; i<row; i++) 
        for(int j=0; j<col;j++)
            mat[i][j] = 1.0;
    return mat;
}


// initialize with random value under max
double** mat_rand(int row, int col, int max){
    double **mat = (double **)malloc(row * sizeof(double*));
    for (int i=0; i<row; i++) 
         mat[i] = (double *)malloc(col * sizeof(double)); 
    for (int i=0; i<row; i++) 
        for(int j=0; j<col;j++)
            mat[i][j] = rand() % max;
    return mat;
}


// Matrix Multiplication
double** mat_mul(int m, int p, int n, double** mat_l, double** mat_r)
{
    double** product = mat_zeros(m, n);
    // Require: mat_l is m x p and mat_r is p x n.
    int i, j, k;
    // matrix multiplication
    for (i = 0; i < m; i++ )
        for (j = 0; j < n; j++ )
            for (k = 0; k < p; k++ )
                product[i][j] += mat_l[i][k] * mat_r[k][j];
    return product;
}


// Matrix Transpose
double** mat_trans(int row, int col, double** mat_old)
{
    double** mat_new = mat_zeros(row, col);
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            mat_new[j][i] = mat_old[i][j];
        }
    }
    return mat_new;
}


// Construct diagonal matrix from vector
double** mat_diag(int col, double** arr)
{
    double** mat = mat_zeros(col, col);
    for(int i=0; i<col; i++){           
        mat[i][i] = arr[0][i];
    }
    return mat;
}


double** mat_add(int m, int n, double** mat1, double** mat2)
{
    double** result = mat_zeros(m, n);
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
    return result;
}


/*For calculating Determinant of the Matrix */
double determinant(int init_k, int order, double** a)
{
    double s = 1, det = 0;
    double** b = mat_zeros(init_k, init_k);
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
double** inverse(int f, double** num)
{
    double det = determinant(f,f, num);
    if(det == 0.0){
        printf("Inverse of this matrix is impossible!\n");
        return NULL;
    }
    else{
        double** b = mat_zeros(f,f);
        double** fac = mat_zeros(f,f);
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

        double** inv_num = mat_trans(f,f, fac);

        for(int i=0; i<f; i++){
            for(int j=0; j<f; j++){
                inv_num[i][j] = inv_num[i][j]/det;
            }
        }
        return inv_num;
    }
}