#ifndef MAT_OPS
#define MAT_OPS
#include <inttypes.h>
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"

int easy_rand(int min, int max);

void s_xorshift96(uint32_t usr_def_seed);

uint32_t xorshift96(int min, int max);

double* init_arr(int length);

double** mat_zeros(int row, int col);

double** mat_ones(int row, int col);

double** mat_rand(int row, int col, int max);

double** mat_mul(int m, int p, int n, double** mat_l, double** mat_r);

double** mat_trans(int row, int col, double** mat_old);

double** mat_diag(int col, double** arr);

double** mat_add(int m, int n, double** mat1, double** mat2);

double determinant(int init_k, int order, double** a);

double** inverse(int f, double** num);

#endif



