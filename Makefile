CC = gcc
TARGET_TMO = test_mat_ops
TARGET_TALG = test_alg

test_alg: test_alg.c  alg_lomv.o  mat_ops.o 
	$(CC) -o $(TARGET_TALG) test_alg.c  alg_lomv.o  mat_ops.o 

test_mem_leak: test_mem_leak.c mat_ops.o 
	$(CC) -o test_mem_leak	test_mem_leak.c	 mat_ops.o 

test_mat_ops: test_mat_ops.c mat_ops.o
	$(CC) -o $(TARGET_TMO) test_mat_ops.c mat_ops.o


alg_lomv.so: mat_ops.o alg_lomv.c
	$(CC) -shared -o alg_lomv.so mat_ops.o alg_lomv.c


mat_ops.o: mat_ops.c
	$(CC) -c -o mat_ops.o mat_ops.c

alg_lomv.o: alg_lomv.c mat_ops.o
 


clean:
	-rm –f test_mat_ops
	-rm -f *.o *.so