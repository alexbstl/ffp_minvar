#include "mat_ops.h"

int main(){
    double** test_ptr = mat_rand(4, 5, 20);
    free_ptr(4, test_ptr);
}