#include "mat_ops.h"


void mat_zeros_test(){
    double mat[4][4];
    mat_zeros(4,4, mat);
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
    double mat[1][5];
    mat_ones(1,5,mat);
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
    double mat[3][3] = {{3,0,2}, {2,0, -2}, {0,1,1}};
    double mat_new[3][3];
    mat_trans(3,3,mat, mat_new);
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("%f  ",  mat[i][j]);
        }
        printf("\n");
    }
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("%f  ",  mat_new[i][j]);
        }
        printf("\n");
    }
}


void mat_diag_test(){
    double vec[2][1] = {{3},{4}};
    double mat[2][2];
    mat_diag(2, vec, mat);
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            printf("%f  ",  mat[i][j]);
        }
        printf("\n");
    }

    double vec3[3][1] = {{3},{4},{5}};
    double mat3[3][3];
    mat_diag(3, vec3, mat3);
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("%f  ",  mat3[i][j]);
        }
        printf("\n");
    }
}


void mat_determiant_test(){
    double mat1[1][1] = {7};
    double mat2[2][2] = {{4,6},{3,8}};
    double mat3[3][3] = {{3,0,2}, {2,0, -2}, {0,1,1}};
    double det1 = determinant(1,1,mat1);
    double det2 = determinant(2,2,mat2);
    double det3 = determinant(3,3, mat3);
    if(det1 == 7.0){
        printf("Passed: The determinant of order 1 matrix is: %f\n", det1);
    }
    if(det2 == 14.0){
        printf("Passed: The determinant of order 2 matrix is: %f\n", det2);
    }
    printf("determinant of mat3 is: %f\n", det3);
}


void inverse_test(){
    double mat2[2][2] = {{4,6},{3,8}};
    double mat3[3][3] = {{7,2,1}, {0,3,-1}, {-3,4,-2}};
    double mat3_1[3][3] = {{0, -3,-2}, {1,-4,-2}, {-3,4,1}};
    double det2 = determinant(2,2, mat2);
    double det3 = determinant(3,3, mat3);
    inverse(3, mat3);
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("%f  ",  mat3[i][j]);
        }
        printf("\n");
    }
    printf("determinant of mat is: %f\n", det3);
}


int main(){
    clock_t begin = clock();
    double time_used;
    /*
    double  mat2[1][5];
    mat_ones(1,5,mat2);
    printf("%f\n",mat2[3]);*/
    /*mat_zeros_test();
    mat_ones_test();
    mat_init_test();*/
    inverse_test();
    //mat_determiant_test();
    //mat_trans_test();
    mat_diag_test();

    time_used = (double) (clock() - begin) / CLOCKS_PER_SEC;
    printf("time used: %f", time_used);
}
