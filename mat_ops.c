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


// Need to pass by reference
void free_ptr(int r, double **p){
    for(int i=0; i<r; i++){
        free(p[i]);
    }
    free(p);
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
double** mat_rand(int row, int col, double min, double max){
    double **mat = (double **)malloc(row * sizeof(double*));
    for (int i=0; i<row; i++) 
         mat[i] = (double *)malloc(col * sizeof(double)); 
    for (int i=0; i<row; i++) 
        for(int j=0; j<col;j++)
            mat[i][j] = min + (rand() /(RAND_MAX / (max - min)));
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


/* This determinant use Doolittle LU decomposition to calculate determinant 
   det(mat) = det(L)det(U) = det(U) = d1*d2*....*dk, where dk are the diagonal entries. */

double determinant(int dim, double** mat){
    // Gaussian elimination
    double ratio = 0;
    for(int i=0;i<dim;i++){
		if(mat[i][i] == 0.0){
		    printf("Mathematical Error!");
		    exit(0);
	    }
		for(int j=i+1;j<dim;j++){
			ratio = mat[j][i]/mat[i][i];
			for(int k=i; k<dim; k++){
			  	mat[j][k] = mat[j][k] - ratio*mat[i][k];
			}
		}
	}

    double det = 1;
    for(int i=0; i<dim; i++){
        det = det* mat[i][i];
    }
    return det;
}


// Default requirement: mat is squre.
// 1. calculate cofactor(mat)
// 2. adj(mat) = C^T
// 3. inv(mat = adj(mat)/det(mat)
double** inverse(int dim, double** mat)
{
    double det = determinant(dim, mat);
    if(det == 0.0){
        printf("Inverse of this matrix is impossible!\n");
        return NULL;
    }
    else{
        // 1. calculate cofactor(mat)
        double** cofactor = mat_zeros(dim, dim);
        // cofactor_ij = (-1)^(i+j) * Minor_ij
        for(int i=0; i<dim; i++){
            for(int j=0; j<dim; j++){
                // construct minor matrix of element A_ij, 
                // for purpose of calculating determinant
                double** minor = mat_zeros(dim-1, dim-1);
                for(int p=0; p<dim-1; p++){
                    for(int q=0; q<dim-1; q++){
                        if(p!=i && q==j){
                            minor[p][q] = mat[i][j+1];
                        }
                        if(p==i && q!=j){
                            minor[p][q] = mat[i+1][j];
                        }
                        if(p==i && q==j){
                            minor[p][q] = mat[i+1][j+1];
                        }
                        if(p!=i && q!=j){
                            minor[p][q] = mat[i][j];
                        }
                    }
                }
                cofactor[i][j] = (double)pow(-1, i+j)  * determinant(dim-1, minor);
                free_ptr(dim-1, minor);
            }
        }

        // 2. adj(mat) = C^T
        double** adjoint = mat_trans(dim, dim, cofactor);
        free_ptr(dim, cofactor);

        // 3. inv(mat = adj(mat)/det(mat)
        double** inv = mat_zeros(dim,dim);
        for(int i=0; i<dim; i++){
            for(int j=0; j<dim; j++){
                inv[i][j] = adjoint[i][j] / det;
            }
        }
        free_ptr(dim, adjoint);
        return inv;
    }
}


void print_mat(int r, int c, double** mat){
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            printf("%f  ",  mat[i][j]);
        }
        printf("\n");
    }
}

// both dimension of **new should be greater than **old
void copy_mat(int r, int c, double** new, double** old){
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            new[i][j] = old[i][j];
        }
    }
}