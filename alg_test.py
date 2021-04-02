# alg_lomv_test.py
import ctypes
from ctypes import *
import pathlib
import numpy as np
import time
import pdb


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


# numpy C-API stores ndarrays (or matrices for that matter) with a single pointer


# numeric solver result. Not our alg.
"""
def lo_numeric():
    q = matrix(np.zeros(N), tc='d')
    h = matrix(np.zeros(N), tc='d')
    G = matrix(-1.0 * IN, tc='d')
    A = matrix(np.ones(N), tc='d').trans()
    b = matrix([1], tc='d')

    sol = solvers.qp(matrix(2 * Sigma), q, G, h, A, b)
    w = [x for plist in np.asarray(sol['x']) for x in plist]

    return np.asarray(w)
"""


"""
input: 
    theta: np.zeros
    B: ndarray
    V: ndarray
    Delta: ndarray
output: 
"""
# theta need to be created as np.zeros(shape=(K,1))
def psi_test(theta, B, V, Delta):
    theta_ctype = ndarr2ptrs(theta)
    B_ctype = ndarr2ptrs(B)
    V_ctype = ndarr2ptrs(V)
    Delta_ctype = ndarr2ptrs(Delta)
    
    p = B.shape[0]
    q = B.shape[1]

    # Load the shared library into ctypes
    libname = pathlib.Path().absolute() / "alg_lomv.so"
    alg_lib = ctypes.CDLL(libname)
    psi = alg_lib.psi

    #psi.argtypes = [ctypes.c_int, ctypes.c_int,POINTER(c_double), POINTER(POINTER(c_double)),POINTER(POINTER(c_double)),POINTER(POINTER(c_double))]
    psi.restype = POINTER(POINTER(c_double))

    th = psi(p, q, (theta_ctype), (B_ctype), (V_ctype), (Delta_ctype))

    return th


def ffp_test(theta, B, V, Delta):
    theta_ctype = ndarr2ptrs(theta)
    B_ctype = ndarr2ptrs(B)
    V_ctype = ndarr2ptrs(V)
    Delta_ctype = ndarr2ptrs(Delta)
    
    p = B.shape[0]
    q = B.shape[1]

    # Load the shared library into ctypes
    libname = pathlib.Path().absolute() / "alg_lomv.so"
    alg_lib = ctypes.CDLL(libname)
    ffp = alg_lib.ffp

    ffp.restype = POINTER(POINTER(c_double))

    th = ffp(p, q, theta_ctype, B_ctype, V_ctype, Delta_ctype)

    return th



if __name__ == "__main__":

    #---------------- Initialize numbers ----------------#
    
    srng = np.random.RandomState

    N = 500  # number of securities
    K = 4  # number of factors

    # seed for beta and other factor exposures

    seed = np.random.randint(0, 100000)
    seed = 31877
    fmrng = srng(seed)

    ones = np.ones(N)
    IN = np.diag(ones)


    # factor volatilities and variances
    fvol = fmrng.exponential(5, K) / 100
    fvar = fvol ** 2

    # specific variance
    svol = fmrng.uniform(0, 100, N) / 100
    svar = svol ** 2 ## svar: Z
    D = np.diag(svar)

    # construct the factor matrix B
    B = np.zeros((N, K))
    for k in range(K):
        cents = np.array([0, 1 / 4, 1 / 2, 3 / 4, 1])
        disps = np.array([1 / 8, 1 / 4, 1 / 2, 3 / 4, 1])
        cent = fmrng.choice(cents)
        disp = fmrng.choice(disps)
        sgn = fmrng.choice([-1.0, 1.0])
        beta = fmrng.normal(sgn * cent, disp, N)
        B[:, k] = beta

    V = np.diag(fvar)

    #---------------------- Psi Test ----------------------------#
    theta = psi_test(np.zeros(shape=(K,1)), B, V, D)  
    for i in range(K):
        print(theta[i][0])
