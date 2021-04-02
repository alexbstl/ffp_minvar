import ctypes
from ctypes import *
import pathlib
import numpy as np
import time


# helper function to help convert numpy array to 
# the double** in c functions
def ndarr2ptrs(arr):
    if(arr.ndim == 2):
        row = arr.shape[0]
        col = arr.shape[1]
        dest = ((ctypes.c_double * col) * row) ()
        temp = (POINTER(c_double) * row) ()
        for i in range(row):
            for j in range(col):
                dest[i][j] = arr[i][j]

        for i in range(row):
            temp[i] = dest[i]
    else:
        row = 1
        col = arr.shape[0]

        dest = ((ctypes.c_double * col) * row) ()
        temp = (POINTER(c_double) * row) ()

        for i in range(row):
            for j in range(col):
                dest[i][j] = arr[j]

        for i in range(row):
            temp[i] = dest[i]

    return temp



def test_psi():
    #---------------- 1.Initialize numbers ----------------#
    N = 500
    K = 4
    theta = np.random.randint(5, size=(K,1))
    print(theta)
   
    #---------------- 2. Transforming to Ctypes ----------------#
    """
    theta_ctype = ndarr2ptrs(np.zeros(shape=(K,1)))
    print(theta_ctype[0][0])
    B_ctype = ndarr2ptrs(B)
    V_ctype = ndarr2ptrs(V)
    Delta_ctype = ndarr2ptrs(D)
    """

    #for i in range(500):
     #   for j in range(500):
      #      print(Delta_ctype[i][j]," ")
       # print("\n")



if __name__ == "__main__":
    test_psi()