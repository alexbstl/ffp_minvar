#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_linalg.h>


void test_matmul(){
    int i, j;

    gsl_matrix * m1 = gsl_matrix_alloc(10, 4);
    gsl_matrix * m2 = gsl_matrix_alloc(10, 4);
    for(i=0; i<10; i++){
        for(j=0; j<4; j++){
            gsl_matrix_set(m1, i, j, rand() % 10);
        }
    }

    for(i=0; i<10; i++){
        for(j=0; j<4; j++){
            gsl_matrix_set(m2, i, j, rand() % 10);
        }
    }

    printf("m1 before matmul:\n");
    for (i = 0; i < 10; i++){
        for (j = 0; j < 4; j++){
            printf ("%g  ", gsl_matrix_get (m1, i, j));
        }
        printf("\n");
    }

    gsl_matrix * result = gsl_matrix_alloc(4, 4);

    gsl_blas_dgemm(CblasTrans, CblasNoTrans, 1.0, m1, m2, 0.0, result);

    printf("m1 after matmul:\n");
    for (i = 0; i < 10; i++){
        for (j = 0; j < 4; j++){
            printf ("%g  ", gsl_matrix_get (m1, i, j));
        }
        printf("\n");
    }

    printf("matmul result:\n");
    for (i = 0; i < 4; i++){
        for (j = 0; j < 4; j++){
            printf ("%g ", gsl_matrix_get (result, i, j));
        }
        printf("\n");
    }

    // gsl_matrix_fprintf(stdout, result, "%g");

    gsl_matrix_free(m1);
    gsl_matrix_free(m2);
    gsl_matrix_free(result);

}

void test_mat_inverse(){
    int i, j;
    double m1_data[] = {4, 7,
                        2, 6};
    gsl_matrix_view m1 = gsl_matrix_view_array(m1_data, 2, 2);
    int s;
    gsl_permutation * p1 = gsl_permutation_alloc(2);
    gsl_matrix * m1_inv = gsl_matrix_alloc(2, 2);
    gsl_linalg_LU_decomp(&m1.matrix, p1, &s);
    gsl_linalg_LU_invert(&m1.matrix, p1, m1_inv);
    printf("Inverse of 2x2 matrix:\n");
    for (i = 0; i < 2; i++){
        for (j = 0; j < 2; j++){
            printf ("%g ", gsl_matrix_get (m1_inv, i, j));
        }
        printf("\n");
    }

    double m2_data[] = {7, 2, 1,
                        0, 3, -1,
                        -3, 4, -2};
    gsl_matrix_view m2 = gsl_matrix_view_array(m2_data, 3, 3);
    gsl_permutation * p2 = gsl_permutation_alloc(3);
    gsl_matrix * m2_inv = gsl_matrix_alloc(3, 3);
    gsl_linalg_LU_decomp(&m2.matrix, p2, &s);
    gsl_linalg_LU_invert(&m2.matrix, p2, m2_inv);
    printf("Inverse of 3x3 matrix:\n");
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            printf ("%g ", gsl_matrix_get (m2_inv, i, j));
        }
        printf("\n");
    }

    double m3_data[] = {6, 4, 2, 8,
                        1, 3, 5, 7,
                        2, 3, 5, 6,
                        4, 2, 6, 3};
    gsl_matrix_view m3 = gsl_matrix_view_array(m3_data, 4, 4);
    gsl_permutation * p3 = gsl_permutation_alloc(4);
    gsl_matrix * m3_inv = gsl_matrix_alloc(4, 4);
    gsl_linalg_LU_decomp(&m3.matrix, p3, &s);
    gsl_linalg_LU_invert(&m3.matrix, p3, m3_inv);
    printf("Inverse of 4x4 matrix:\n");
    for (i = 0; i < 4; i++){
        for (j = 0; j < 4; j++){
            printf ("%g ", gsl_matrix_get (m3_inv, i, j));
        }
        printf("\n");
    }
    
    // gsl_matrix_fprintf(stdout, m3_inv, "%g");

}


int main(){
    test_matmul();
    //test_mat_inverse();
}