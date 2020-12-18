#include "mat_ops.h"



int main(){
    clock_t begin = clock();
    double time_used;

    //---------------- Dim of 2 -------------------//
    double** mat2 = mat_zeros(2, 2);
    /*
    mat2[0][0] = 2;
    mat2[0][1] = 4;
    mat2[1][0] = 0;
    mat2[1][1] = 1;*/
    mat2[0][0] = 9;
    mat2[0][1] = 0;
    mat2[1][0] = 0;
    mat2[1][1] = 4;


    int dim2 = 2;
    double** inv2 = inv(dim2, mat2);

    print_mat(dim2, dim2, mat2);
    print_mat(dim2, dim2, inv2);

    free_ptr(dim2, mat2);
    free_ptr(dim2, inv2);
    

    //---------------- Dim of 3 -------------------//
    double** mat3 = mat_zeros(3, 3);
    /*
    mat3[0][0] = 0;
    mat3[0][1] = 0;
    mat3[0][2] = 1;
    mat3[1][0] = 1;
    mat3[1][1] = 0;
    mat3[1][2] = 2;
    mat3[2][0] = 0;
    mat3[2][1] = 3;
    mat3[2][2] = 0;*/
    
    /*
    mat3[0][0] = 0;
    mat3[0][1] = -3;
    mat3[0][2] = -2;
    mat3[1][0] = 1;
    mat3[1][1] = -4;
    mat3[1][2] = -2;
    mat3[2][0] = -3;
    mat3[2][1] = 4;
    mat3[2][2] = 1;*/

    mat3[0][0] = 2;
    mat3[0][1] = 0;
    mat3[0][2] = 0;
    mat3[1][0] = 0;
    mat3[1][1] = 3;
    mat3[1][2] = 0;
    mat3[2][0] = 0;
    mat3[2][1] = 0;
    mat3[2][2] = 5;

    int dim3 = 3;
    double** inv3 = inv(dim3, mat3);

    // print test: dim of 3
    print_mat(dim3, dim3, mat3);
    print_mat(dim3, dim3, inv3);
    // free pointers: dim of 2
    free_ptr(dim3, mat3);
    free_ptr(dim3, inv3);

    time_used = (double) (clock() - begin) / CLOCKS_PER_SEC;
    printf("time used: %f\n", time_used);
}