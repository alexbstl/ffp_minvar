import ctypes
from ctypes import *
import numpy as np


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


if __name__ == "__main__":

    arr = np.random.uniform(low=0, high=13.3, size=(4,5))
    arr_ptr = ndarr2ptrs(arr)
    print(arr_ptr[2][3])
