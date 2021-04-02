#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>

int main(){
    int i, j;

    gsl_matrix * m1 = gsl_matrix_alloc(10, 4);
    gsl_matrix * m2 = gsl_matrix_alloc(4, 10);
    for(i=0; i<10; i++){
        for(j=0; j<4; j++){
            gsl_matrix_set(m1, i, j, rand() % 10);
        }
    }

    for(i=0; i<4; i++){
        for(j=0; j<10; j++){
            gsl_matrix_set(m2, i, j, rand() % 10);
        }
    }

    for (i = 0; i < 10; i++){
        for (j = 0; j < 4; j++){
            printf ("m(%d,%d) = %g\n", i, j, gsl_matrix_get (m1, i, j));
        }
    }

    gsl_matrix * result = gsl_matrix_alloc(10, 10);

    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, m1, m2, 0.0, result);

    for (i = 0; i < 10; i++){
        for (j = 0; j < 4; j++){
            printf ("%g ", gsl_matrix_get (result, i, j));
        }
        printf("\n");
    }

    gsl_matrix_free(m1);
    gsl_matrix_free(m2);
    gsl_matrix_free(result);

}