#include "stdio.h"
#include "stdlib.h"

double** mat_zeros(int row, int col){
    double **mat = malloc(row * sizeof(*mat));
    for (int i=0; i<row; i++) 
        mat[i] = malloc(col * sizeof(mat[0])); 
    for (int i=0; i<row; i++) 
        for(int j=0; j<col;j++)
            mat[i][j] = 1.0;
    return mat;
}

int main(){
    double** mat = mat_zeros(3,4);
    for (int i=0; i<3; i++) 
        for(int j=0; j<4; j++)
            printf("%0.16f ", mat[i][j]);
        printf("\n");
}
