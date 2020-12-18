CC = gcc
TARGET_TMO = test_mat_ops
TARGET_TALG = test_alg

test_alg: alg_lomv.o mat_ops.o test_alg.c  
	$(CC) -o test_alg test_alg.c alg_lomv.o mat_ops.o -lm -g 

test_mem_leak: mat_ops.o test_mem_leak.c 
	$(CC) -o test_mem_leak	test_mem_leak.c	 mat_ops.o -lm -g

test_mat_ops: mat_ops.o test_mat_ops.c 
	$(CC) -o $(TARGET_TMO) test_mat_ops.c mat_ops.o -lm -g

test_gaussian: mat_ops.o test_gaussian.c  
	$(CC) -o test_gaussian mat_ops.o test_gaussian.c -lm -g 


gaussian.o: gaussian.c
	$(CC) -c -o gaussian.o gaussian.c -g

alg_lomv.o: alg_lomv.c
	$(CC) -c -o alg_lomv.o alg_lomv.c -g

alg_lomv.so: mat_ops.o alg_lomv.c
	$(CC) -shared -o alg_lomv.so mat_ops.o alg_lomv.c

mat_ops.o: mat_ops.c
	$(CC) -c -o mat_ops.o mat_ops.c -g


 
clean:
	-rm -f *.o *.so