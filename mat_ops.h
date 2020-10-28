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

void mat_zeros(int rows, int cols, double mat[rows][cols]);

void mat_ones(int rows, int cols, double mat[rows][cols]);

void mat_mul(int m, int p, int n, double product[m][n], double mat_l[m][p], double mat_r[p][n]);

void mat_trans(int rows, int cols, double mat_old[rows][cols], double mat_new[cols][rows]);

void mat_diag(int length, double vec[length][1], double mat[length][length]);

void mat_add(int m, int n, double result[m][n], double mat1[m][n], double mat2[m][n]);

double determinant(int init_k, int order, double a[init_k][init_k]);

void inverse(int f, double num[f][f]);

#endif



