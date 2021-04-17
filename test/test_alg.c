#include "../include/alg_lomv.h"

double test_linf(){
    int i;
    int q = 4;
    gsl_vector * a = gsl_vector_alloc(q);
    for(i=0; i<q; i++){
        gsl_vector_set(a, i, rand()%10);
    }
    gsl_vector * b = gsl_vector_alloc(q);
    for(i=0; i<q; i++){
        gsl_vector_set(b, i, rand()%10);
    }

    double result = linf(q, a, b);
    gsl_vector_free(a);
    gsl_vector_free(b);

    return result;
}


/*
void test_psi_1(){
    int i, j;
    int p = 50;
    int q = 4;
    gsl_vector * theta = gsl_vector_alloc(q);
    for(i=0; i<q; i++){
        gsl_vector_set(theta, i, rand()%10);
    }
    // gsl_vector_set_zero(theta);

    gsl_matrix * B = gsl_matrix_alloc(p, q);
    for(i=0; i<p; i++){
        for(j=0; j<q; j++){
            gsl_matrix_set(B, i, j, rand()%20);
        }
    }

    gsl_matrix * V = gsl_matrix_alloc(q, q);
    for(i=0; i<q; i++){
        for(j=0; j<q; j++){
            gsl_matrix_set(V, i, j, rand()%20);
        }
    }

    gsl_vector * Delta = gsl_vector_alloc(p);
    for(i=0; i<p; i++){
        gsl_vector_set(Delta, i, 1+rand()%10);
    }
    // gsl_vector_fprintf(stdout, Delta, "%g");
    gsl_vector * x = psi(p, q, theta, B, V, Delta);

    gsl_vector_fprintf(stdout, x, "%g");
} 
*/


void test_ffp_1(){
    int i, j;
    int p = 500;
    int q = 4;
    gsl_vector * theta = gsl_vector_alloc(q);
    for(i=0; i<q; i++){
        gsl_vector_set(theta, i, rand()%10);
    }
    // gsl_vector_set_zero(theta);

    gsl_matrix * B = gsl_matrix_alloc(p, q);
    for(i=0; i<p; i++){
        for(j=0; j<q; j++){
            gsl_matrix_set(B, i, j, rand()%20);
        }
    }

    gsl_matrix * V = gsl_matrix_alloc(q, q);
    for(i=0; i<q; i++){
        for(j=0; j<q; j++){
            gsl_matrix_set(V, i, j, rand()%20);
        }
    }

    gsl_vector * Delta = gsl_vector_alloc(p);
    for(i=0; i<p; i++){
        gsl_vector_set(Delta, i, 1+rand()%10);
    }

    gsl_vector * w = ffp(p, q, theta, B, V, Delta);
    gsl_vector_fprintf(stdout, w, "%f");
} 


void test_lo_minvar(){
    int i, j;
    int p = 50;
    int q = 4;

    gsl_matrix * B = gsl_matrix_alloc(p, q);
    for(i=0; i<p; i++){
        for(j=0; j<q; j++){
            gsl_matrix_set(B, i, j, rand()%20);
        }
    }

    gsl_matrix * V = gsl_matrix_alloc(q, q);
    for(i=0; i<q; i++){
        for(j=0; j<q; j++){
            gsl_matrix_set(V, i, j, rand()%20);
        }
    }

    gsl_vector * Delta = gsl_vector_alloc(p);
    for(i=0; i<p; i++){
        gsl_vector_set(Delta, i, 1+rand()%10);
    }

    gsl_vector * w = lo_minvar(p, q, B, V, Delta);

    printf("w is right here:-------------\n");
    gsl_vector_fprintf(stdout, w, "%g");
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
    printf("Testing ffp function with some random numbers:\n");
    test_ffp_1();
    printf("Testing lo_minvar function with some random numbers:\n");
    test_lo_minvar();

    time_used = (double) (clock() - begin) / CLOCKS_PER_SEC;
    printf("time used: %f\n", time_used);
}