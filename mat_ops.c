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
void xorshift96_seeding(uint32_t usr_def_seed){
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


// Initialize a Matrix of No Values
float **mat_init(int rows, int cols){
    float **mat = (float **)malloc(rows * sizeof(float *)); 
    for(int i=0; i<rows; i++){
        mat[i] = (float *)malloc(cols * sizeof(float));
    }
    return mat;
}


// Create Matrix of Zeros
float **mat_zeros(int rows, int cols){
    float **mat = (float **)malloc(rows * sizeof(float *)); 
    for(int i=0; i<rows; i++){
        mat[i] = (float *)calloc(cols, sizeof(float));
    }
    return mat;
}


// Create Matrix of Ones
float **mat_ones(int rows, int cols){
    float **mat = mat_init(rows, cols); 
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            mat[i][j] = 1.0;
        }
    }
    return mat;
}


// Matrix Multiplication
float **mat_mul(float **mat_l, float **mat_r, int m, int p, int n) {
    // Require: mat_l is m x p and mat_r is p x n.
    int i, j, k;
    float **product = mat_zeros(m,n);
    // matrix multiplication
    for (i = 0; i < m; i++ )
        for (j = 0; j < n; j++ )
            for (k = 0; k < p; k++ )
                product[i][j] += mat_l[i][k]*mat_r[k][j];
    return product;
}


// Matrix Transpose
float **mat_trans(float **mat_old, int rows, int cols){
    float **mat_new = mat_init(cols, rows);
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            mat_new[j][i] = mat_old[i][j];
        }
    }
    return mat_new;
}






// Free memory
void mat_clean(float **mat, int rows, int cols){
    for(int i=0; i<rows; i++)
        free(mat[i]);
    free(mat);
}
