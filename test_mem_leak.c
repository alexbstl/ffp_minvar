#include "mat_ops.h"

// Need to pass by reference
void free_ptr(int r, double **p){
    for(int i=0; i<r; i++){
        free(p[i]);
    }
    free(p);
}

int main(){
    double** test_ptr = mat_rand(4, 5, 20);
}