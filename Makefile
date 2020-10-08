CC = gcc
TARGET_TMO = test_mat_ops

$(TARGET_TMO): test_mat_ops.c mat_ops.o
	$(CC) -o $(TARGET_TMO) test_mat_ops.c mat_ops.o

mat_ops.o: mat_ops.c
	$(CC) -c -o mat_ops.o mat_ops.c

clean:
	-rm –f test_mat_ops
	-rm -f *.o