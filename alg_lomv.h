#ifndef ALG_LOMV
#define ALG_LOMV

#include "mat_ops.h"
#include "gaussian.h"
#include "string.h"

int add(int a, int b);

double linf(int row, int col, double** a, double** b);

double** psi(int p, int q, double** theta, double** B, double** V, double** Delta);

double** ffp(int p, int q, double** theta, double** B, double** V, double** Delta);

double** lo_minvar(int p, int q, double** B, double** V, double** Delta);

#endif
