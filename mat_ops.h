#ifndef MAT_OPS
#define MAT_OPS
#include <inttypes.h>
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int easy_rand(int min, int max);

void xorshift96_seeding(uint32_t usr_def_seed);

uint32_t xorshift96(int min, int max);

float **mat_init(int rows, int cols);

float **mat_zeros(int rows, int cols);

float **mat_ones(int rows, int cols);

float **mat_mul(float **mat_l, float **mat_r, int m, int p, int n);

float **mat_trans(float **mat_old, int rows, int cols);

void mat_clean(float **mat, int rows, int cols);

#endif



