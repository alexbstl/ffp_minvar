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
    double** mat = mat_ones(5,1);
    if(mat[0][0]==1){
        printf("Passed: Entry at row 0 col 0 is 1!\n");
    }
    else{
        printf("Test Failed: row 0 col 0.\n");
    }
    if(mat[3][0]==1){
        printf("Passed: Entry at row 3 col 0 is 1!\n");
    }
    else{
        printf("Test Failed: row 0 col 3.\n");
    }
}


void mat_trans_test(){
    double** mat = mat_rand(3,5, 0,50);
    double** mat_new = mat_trans(3,5, mat);
    printf("Original Matrix\n");
    print_mat(3,5, mat);
    printf("Transpose Matrix\n");
    print_mat(5,3, mat_new);

    free_ptr(3, mat);
    free_ptr(5, mat_new);

}


void mat_diag_test(){
    int i;
    double** vec = mat_zeros(1,3);
    vec[0][0] = 3;
    vec[0][1] = 4;
    vec[0][2] = 5;
    double** mat = mat_diag(3, vec);
    printf("Original Array\n");
    print_mat(1,3, mat);

    printf("Diagonal Matrix\n");
    print_mat(3,3, mat);

}



void inverse_test(){
    double** mat2 = mat_zeros(2, 2);
    mat2[0][0] = 4;
    mat2[0][1] = 7;
    mat2[1][0] = 2;
    mat2[1][1] = 6;

    double** mat3 = mat_zeros(3, 3);
    mat3[0][0] = 2;
    mat3[0][1] = 2;
    mat3[0][2] = 0;
    mat3[1][0] = -2;
    mat3[1][1] = 3;
    mat3[1][2] = 10;
    mat3[2][0] = 2;
    mat3[2][1] = -3;
    mat3[2][2] = 0;

    double** mat5 = mat_zeros(5, 5);
    mat5[0][0] = 1;
    mat5[1][1] = 22;
    mat5[2][2] = 26;
    mat5[3][3] = -4;
    mat5[4][4] = 7;


    double** inv2 = inv(2, mat2);
    printf("Inverse of order 2 matrix\n");
    print_mat(2,2, inv2);


    double** inv3 = inv(3, mat3);
    printf("Inverse of order 3 matrix\n");
    print_mat(3,3, inv3);
    

    double** inv5 = inv(5, mat5);
    printf("Inverse of order 5 matrix\n");
    print_mat(5,5, inv5);


    free_ptr(2, mat2);
    free_ptr(3, mat3);
    free_ptr(5, mat5);
    free_ptr(2, inv2);
    free_ptr(3, inv3);
    free_ptr(5, inv5);
    
}


int main(){
    clock_t begin = clock();
    double time_used;

    //mat_zeros_test();
    //mat_ones_test();
    mat_trans_test();
    //mat_diag_test();
    //mat_determiant_test();
    //inverse_test();

    time_used = (double) (clock() - begin) / CLOCKS_PER_SEC;
    printf("time used: %f", time_used);
}
