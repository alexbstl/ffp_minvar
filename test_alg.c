#include "alg_lomv.h"

double test_linf(){
    int length = 5;
    double** a = mat_rand(1,5,0, 20);
    double** b = mat_rand(1,5,0, 15);
    free_ptr(1,a);
    free_ptr(1,b);
    return linf(1, length, a, b);
}


void test_psi_1(){
    double** theta = mat_zeros(4,1);
    double** B = mat_rand(10,4,0, 30);
    double** V = mat_rand(4,4,0, 30);
    double** arr = mat_rand(1,10,0, 30);
    double** Delta = mat_diag(10, arr);
    
    double** x = psi(10, 4, theta, B, V, Delta);
    free_ptr(4, theta);
    free_ptr(10, B);
    free_ptr(4, V);
    free_ptr(1, arr);
    free_ptr(10, Delta);

    print_mat(4,1,x);
    free_ptr(4, x);
} 

void test_ffp_1(){
    double** theta = mat_zeros(4,1);
    double** B = mat_rand(10,4,0, 30);
    double** V = mat_rand(4,4,0, 30);
    double** arr = mat_rand(1,10,0, 30);
    double** Delta = mat_diag(10, arr);
    

    double** w = ffp(10, 4, theta, B, V, Delta);
    free_ptr(4, theta);
    free_ptr(10, B);
    free_ptr(4, V);
    free_ptr(1, arr);
    free_ptr(10, Delta);

    print_mat(4,1,w);
    free_ptr(4, w);
} 

void test_lo_minvar(){
    double** B = mat_rand(10,4,0, 30);
    double** V = mat_rand(4,4,0, 30);
    double** arr = mat_rand(1,10,0, 30);
    double** Delta = mat_diag(10, arr);
    
    double** w = lo_minvar(10, 4, B, V, Delta);

    free_ptr(10, B);
    free_ptr(4, V);
    free_ptr(1, arr);
    free_ptr(10, Delta);

    print_mat(4,1,w);
    free_ptr(4, w);
} 

// when declaring pointers, definitely 
// DO NOT declare it inside a function call.
// It causes serious memory leak!
int main(){
    clock_t begin = clock();
    double time_used;

    //double result = test_linf();
    //printf("%f\n", result);
    //printf("%f\n", test_linf());
    //test_psi_1();
    // test_ffp_1();
    test_lo_minvar();

    time_used = (double) (clock() - begin) / CLOCKS_PER_SEC;
    printf("time used: %f\n", time_used);
}