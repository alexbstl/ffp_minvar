import ctypes
from ctypes import *
import pathlib
import numpy as np
import time


# helper function to help convert numpy array to 
# the double** in c functions
def ndarr2ptrs(arr):
    row = arr.shape[0]
    col = arr.shape[1]
    dest = ((ctypes.c_double * col) * row) ()

    temp = (POINTER(c_double) * row) ()

    for i in range(row):
        for j in range(col):
            dest[i][j] = arr[i][j]

    for i in range(row):
        temp[i] = dest[i]

    return temp


def test_linf():
    # Load the shared library into ctypes
    libname = pathlib.Path().absolute() / "alg_lomv.so"
    alg_lib = ctypes.CDLL(libname)

    linf = alg_lib.linf
    add = alg_lib.add
    test = alg_lib.test

    #------------- Testing 2D Pointer ------------------------#
    linf.restype = c_double

    test_c = np.random.uniform(low=0, high=10, size=(3,1))
    test_d = np.random.uniform(low=0, high=10, size=(3,1))

    print(test_c)

    test_c_p = ndarr2ptrs(test_c)
    test_d_p = ndarr2ptrs(test_d)

    print(type(test_c_p))
    linf_result = linf(1, 3, test_c_p, test_d_p)
    print(linf_result)
    
    #------------- Testing Single Pointer --------------------#
    test.restype = c_double

    test_a = np.random.uniform(low=0, high=13.3, size=(4,5))
    test_b = np.random.uniform(low=0.5, high=50, size=(3,3))
    #test_arr_a = (ctypes.c_double * len(test_a))(test_a)
    #test_arr_b = (ctypes.c_double * len(test_b))(test_b)
    test_a_p = ndarr2ptrs(test_a)
    test_b_p = ndarr2ptrs(test_b)

    print(test_a)
    print(type(test_a_p))
    test_result = test(test_a_p, test_b_p)
    print(test_result)


# test POINTER(c_double) return type
def test_test_p():
     # Load the shared library into ctypes
    libname = pathlib.Path().absolute() / "alg_lomv.so"
    alg_lib = ctypes.CDLL(libname)
    
    test_p = alg_lib.test_p
    test_p.restype = POINTER(c_double)

    test_a = np.random.uniform(low=0, high=13.3, size=(4,5))
    test_b = np.random.uniform(low=0.5, high=50, size=(3,3))
    test_a_p = ndarr2ptrs(test_a)
    test_b_p = ndarr2ptrs(test_b)

    test_p_result = test_p(test_a_p, test_b_p)
    print(test_p_result)
    print(test_p_result[0])
    print(test_p_result[1])
    print("Single pointer pass!")


# test POINTER(POINTER(c_double)) return type
def test_test_pp():
     # Load the shared library into ctypes
    libname = pathlib.Path().absolute() / "alg_lomv.so"
    alg_lib = ctypes.CDLL(libname)
    
    test_pp = alg_lib.test_pp
    test_pp.restype = POINTER(POINTER(c_double))

    test_a = np.random.uniform(low=0, high=13.3, size=(4,5))
    test_b = np.random.uniform(low=0.5, high=50, size=(3,3))
    test_a_p = ndarr2ptrs(test_a)
    test_b_p = ndarr2ptrs(test_b)

    test_pp_result = test_pp(test_a_p, test_b_p)
    print(test_pp_result)
    print(test_pp_result[0][1])
    print(test_pp_result[1][2])
    print(test_pp_result[1][0])
    print("Double pointer pass!")




if __name__ == "__main__":
    test_test_p()
    test_test_pp()