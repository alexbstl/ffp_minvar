#include "alg_lomv.h"

double test_linf(){
    int length = 5;
    double** a = mat_rand(1,5,20);
    double** b = mat_rand(1,5,15);
    return linf(1, length, a, b);
}


void test_psi(){
    return;
} 

int main(){
    srand(time(NULL));
    //double result = test_linf();
    //printf("%f\n", result);
    //printf("%f\n", test_linf());
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