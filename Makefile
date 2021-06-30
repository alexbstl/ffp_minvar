CC = gcc
LIBS = -lm -lgsl -lgslcblas # gsl flags

SRC_DIR := src
OBJ_DIR := obj
SHARED_DIR := lib/ffp_minvar/shared
TEST_DIR = test

TEST_GSL := $(TEST_DIR)/test_gsl.c
TEST_ALG := $(TEST_DIR)/test_alg.c
ALG_LOMV_SRC := $(SRC_DIR)/alg_lomv.c
ALG_LOMV_OBJ := $(OBJ_DIR)/alg_lomv.o
ALG_LOMV_SO := $(SHARED_DIR)/alg_lomv.so

test_gsl: $(TEST_GSL)
	$(CC) -Wall $(TEST_GSL) $(LIBS) -o test_gsl

test_alg: $(ALG_LOMV_OBJ) $(TEST_ALG)
	$(CC) -Wall $(ALG_LOMV_OBJ) $(TEST_ALG) $(LIBS) -o test_alg -g 

alg_lomv.o: $(TEST_ALG)
	$(CC) -c -o $(ALG_LOMV_OBJ) $(ALG_LOMV_SRC) -g

alg_lomv.so: $(ALG_LOMV_SRC)
	$(CC) -shared -o $(ALG_LOMV_SO) $(ALG_LOMV_SRC) $(LIBS) -g

clean:
	-rm -f *.o *.gch test_gsl test_alg