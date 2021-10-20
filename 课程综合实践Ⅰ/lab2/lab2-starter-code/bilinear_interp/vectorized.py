import numpy as np
from numpy import int64
from numpy import float64


def bilinear_interp_vectorized(a: np.ndarray, b: np.ndarray) -> np.ndarray:
    """
    This is the vectorized implementation of bilinear interpolation.
    - a is a ND array with shape [N, H1, W1, C], dtype = int64
    - b is a ND array with shape [N, H2, W2, 2], dtype = float64
    - return a ND array with shape [N, H2, W2, C], dtype = int64
    """
    # get axis size from ndarray shape
    N = 8
    C = 4
    H2 = 720
    W2 = 1280
    #assert N == N1

    # TODO: Implement vectorized bilinear interpolation
    res = np.empty((N, H2, W2, C),dtype=int64)
    b_x = np.empty((N, H2, W2, 1), dtype=float64)
    b_int_x = np.empty((N, H2, W2, 1), dtype=int)
    b_float_x = np.empty((N, H2, W2, 1))
    b_int_y = np.empty((N, H2, W2, 1), dtype=int)
    b_float_y = np.empty((N, H2, W2, 1))
    b_y = np.empty((N, H2, W2, 1), dtype=float64)
    res_index_00 = np.empty((N, H2, W2, C),dtype=int64)
    res_index_01 = np.empty((N, H2, W2, C),dtype=int64)
    res_index_10 = np.empty((N, H2, W2, C),dtype=int64)
    res_index_11 = np.empty((N, H2, W2, C),dtype=int64)
    #int - float64 + int64

    for i in range (N):
        b_x[i] = b[i].reshape(-1)[::2].reshape(1,720,1280,1)
        b_int_x[i] = b[i].reshape(-1)[::2].reshape(1,720,1280,1).astype(np.int)
        b_float_x[i] = (b_x[i] - b_int_x[i])#.astype(np.float64)
        b_y[i] = b[i].reshape(-1)[1::2].reshape(1,720,1280,1)
        b_int_y[i] = b[i].reshape(-1)[1::2].reshape(1,720,1280,1).astype(np.int)
        b_float_y[i] = (b_y[i] - b_int_y[i])#.astype(np.float64)
    
    for i in range(N):
        res_index_00[i] = a[i][[b[i].astype(np.int).reshape(-1)[::2]],[b[i].astype(np.int).reshape(-1)[1::2]]].reshape(1,720,1280,4)
        res_index_01[i] = a[i][[b[i].astype(np.int).reshape(-1)[::2]],[b[i].astype(np.int).reshape(-1)[1::2]+1]].reshape(1,720,1280,4)
        res_index_10[i] = a[i][[b[i].astype(np.int).reshape(-1)[::2]+1],[b[i].astype(np.int).reshape(-1)[1::2]]].reshape(1,720,1280,4)
        res_index_11[i] = a[i][[b[i].astype(np.int).reshape(-1)[::2]+1],[b[i].astype(np.int).reshape(-1)[1::2]+1]].reshape(1,720,1280,4)
    
    res_index_00 = res_index_00 * (1-b_float_x) * (1-b_float_y)
    res_index_01 = res_index_01 * (1-b_float_x) * (b_float_y)
    res_index_10 = res_index_10 * (b_float_x) * (1-b_float_y)
    res_index_11 = res_index_11 * (b_float_x) * (b_float_y)
    res = (res_index_00 + res_index_01 + res_index_10 + res_index_11).astype(np.int64)
    return res