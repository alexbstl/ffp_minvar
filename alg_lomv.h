#ifndef ALG_LOMV
#define ALG_LOMV

#include "mat_ops.h"
#include "gaussian.h"
#include "string.h"
#include "assert.h"
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_linalg.h>

int add(int a, int b);

double linf(int row, int col, gsl_matrix * a, gsl_matrix * b);

gsl_vector * psi(int p, int q, gsl_vector * theta, gsl_matrix * B, gsl_matrix * V, gsl_vector * Delta);

//double** ffp(int p, int q, double** theta, double** B, double** V, double** Delta);

//double** lo_minvar(int p, int q, double** B, double** V, double** Delta);

#endif
