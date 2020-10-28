#ifndef ALG_LOMV
#define ALG_LOMV

#include "mat_ops.h"

double linf(int length, double a[1][length], double b[1][length]);

void psi(int p, int q, double x[q][1], double theta[q][1], double B[p][q], double V[q][q], double Delta[p][p]);

void ffp(int p, int q, double x[q][1], double theta[q][1], double B[p][q], double V[q][q], double Delta[p][p]);

void lo_minvar(int p, int q, double x[p][1], double B[p][q], double V[q][q], double Delta[p][p]);

#endif
