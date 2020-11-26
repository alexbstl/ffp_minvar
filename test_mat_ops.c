#include "mat_ops.h"


void mat_zeros_test(){
    double** mat = mat_zeros(4,4);
    if(mat[0][0]==0){
        printf("Passed: Entry at row 0 col 0 is 0!\n");
    }
    else{
        printf("Test Failed: row 0 col 0.\n");
    }

    if(mat[1][2]==0){
        printf("Passed: Entry at row 1 col 2 is 0!\n");
    }
    else{
        printf("Test Failed: row 1 col 2.\n");
    }

    if(mat[3][3]==0){
        printf("Passed: Entry at row 3 col 3 is 0!\n");
    }
    else{
        printf("Test Failed: row 3 col 3.\n");
    }
}


void mat_ones_test(){
    double** mat = mat_ones(1,5);
    if(mat[0][0]==1){
        printf("Passed: Entry at row 0 col 0 is 1!\n");
    }
    else{
        printf("Test Failed: row 0 col 0.\n");
    }
    if(mat[0][3]==1){
        printf("Passed: Entry at row 0 col 3 is 1!\n");
    }
    else{
        printf("Test Failed: row 0 col 3.\n");
    }
}


void mat_trans_test(){
    double** mat = mat_rand(3,3, 50);
    double** mat_new = mat_trans(3,3, mat);
    printf("Original Matrix\n");
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("%f  ",  mat[i][j]);
        }
        printf("\n");
    }
    printf("Transpose Matrix\n");
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("%f  ",  mat_new[i][j]);
        }
        printf("\n");
    }
}


void mat_diag_test(){
    int i;
    double** vec = mat_zeros(1,3);
    vec[0][0] = 3;
    vec[0][1] = 4;
    vec[0][2] = 5;
    double** mat = mat_diag(3, vec);
    printf("Original Array\n");
    for(i=0; i<3; i++){
        printf("%f  ",  vec[0][i]);
    }
    printf("\n");
    printf("Diagonal Matrix\n");
    for(i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("%f  ",  mat[i][j]);
        }
        printf("\n");
    }
}


void mat_determiant_test(){
    double** mat1 = mat_zeros(1, 1);
    mat1[0][0] = 7;
    double** mat2 = mat_zeros(2, 2);
    mat2[0][0] = 1;
    mat2[0][1] = 2;
    mat2[1][0] = 3;
    mat2[1][1] = 4;
    double** mat3 = mat_zeros(3, 3);
    mat3[0][0] = 1;
    mat3[0][1] = 3;
    mat3[0][2] = 2;
    mat3[1][0] = -3;
    mat3[1][1] = -1;
    mat3[1][2] = -3;
    mat3[2][0] = 2;
    mat3[2][1] = 3;
    mat3[2][2] = 1;
    double det1 = determinant(1,1,mat1);
    double det2 = determinant(2,2,mat2);
    double det3 = determinant(3,3,mat3);
    if(det1 == 7.0){
        printf("Passed: The determinant of order 1 matrix is: %f\n", det1);
    }
    if(det2 == -2.0){
        printf("Passed: The determinant of order 2 matrix is: %f\n", det2);
    }
    if(det3 == -15.0){
        printf("Passed: The determinant of order 2 matrix is: %f\n", det3);
    }
}



void inverse_test(){
    double** mat2 = mat_zeros(2, 2);
    mat2[0][0] = 4;
    mat2[0][1] = 7;
    mat2[1][0] = 2;
    mat2[1][1] = 6;
    double** inv2 = inverse(2, mat2);

    double** mat3 = mat_zeros(3, 3);
    mat3[0][0] = 4;
    mat3[0][1] = -2;
    mat3[0][2] = 3;
    mat3[1][0] = 8;
    mat3[1][1] = -3;
    mat3[1][2] = 5;
    mat3[2][0] = 7;
    mat3[2][1] = -2;
    mat3[2][2] = 4;

    double** inv3 = inverse(3, mat3);
    printf("Inverse of order 2 matrix\n");
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            printf("%f  ",  inv2[i][j]);
        }
        printf("\n");
    }

    printf("Inverse of order 3 matrix\n");
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("%f  ",  inv3[i][j]);
        }
        printf("\n");
    }
}


int main(){
    clock_t begin = clock();
    double time_used;

    mat_zeros_test();
    mat_ones_test();
    mat_trans_test();
    mat_diag_test();
    mat_determiant_test();
    inverse_test();

    time_used = (double) (clock() - begin) / CLOCKS_PER_SEC;
    printf("time used: %f", time_used);
}
