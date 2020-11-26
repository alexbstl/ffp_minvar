# alg_lomv_test.py
import ctypes
from ctypes import *
import pathlib
import numpy as np


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


# numpy C-API stores ndarrays (or matrices for that matter) with a single pointer
if __name__ == "__main__":
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
    result = test(test_a_p, test_b_p)
    print(result)