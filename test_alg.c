#include "alg_lomv.h"

double test_linf(){
    int length = 5;
    double** a = mat_rand(1,5,20);
    double** b = mat_rand(1,5,15);
    free_ptr(1,a);
    free_ptr(1,b);
    return linf(1, length, a, b);
}


void test_psi_1(){
    double** theta = mat_zeros(4,1);
    double** B = mat_rand(20,4, 30);
    double** V = mat_rand(4,4, 30);
    double** arr = mat_rand(1,20, 30);
    double** Delta = mat_diag(20, arr);
    

    double** x = psi(20, 4, theta, B, V, Delta);
    free_ptr(4, theta);
    free_ptr(20, B);
    free_ptr(4, V);
    free_ptr(1, arr);
    free_ptr(20, Delta);
    //free_ptr(4, x);
} 

// when declaring pointers, definitely 
// DO NOT declare it inside a function call.
// It causes serious memory leak!
int main(){
    //raise(SIGTRAP);
    //srand(time(NULL));
    //double result = test_linf();
    //printf("%f\n", result);
    //printf("%f\n", test_linf());
    test_psi_1();
    //free_ptr(4, x);
/*
    for(int i=0; i<5; i++){
        a[i] = (double) (rand() % 51);
    }
    for(int i=0; i<5; i++){
        b[i] = (double) (rand() % 51);
    }
    double result = test(a, b);

    printf("%f\n", result);

    int row = 3;
    int col = 4;
    double **arr = (double **)malloc(row * sizeof(double*));
    for (int i=0; i<row; i++) 
         arr[i] = (double *)malloc(col * sizeof(double)); 
    
    for (int i = 0; i < row; i++) 
      for (int j = 0; j < col; j++) 
         printf("%f ", arr[i][j]); */

}