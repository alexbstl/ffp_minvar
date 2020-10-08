#include "mat_ops.h"

void test_xorshift96(void){
    xorshift96_seeding((uint32_t) time(0));
    for (int i=0; i<10; i++){
        printf("xorshif %"PRIu32"\n", xorshift96(0, 10000));
    }
}

int main(){
    clock_t begin = clock();
    test_xorshift96();

    /*
    srand(time(0));
    printf("%d\n", easy_rand(0, 10000));*/
}

