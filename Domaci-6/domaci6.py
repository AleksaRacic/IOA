import scipy
import numpy as np

zarade = [-10, -8, -6, -9, -18, -20, -15, -17, -15, -16, -13, -17]

conditions = [
    [5, 0, 0, 0, 6, 0, 0, 0, 13, 0, 0, 0],
    [0, 7, 0, 0, 0, 12, 0, 0, 0, 14, 0, 0],
    [0, 0, 4, 0, 0, 0, 8, 0, 0, 0, 9, 0],
    [0, 0, 0, 10, 0, 0, 0, 15, 0, 0, 0, 17],
    [1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1]
]

bounds = [2880, 2880, 2880, 2880, 1000, 600, 500]

if __name__ == '__main__':
    res = scipy.optimize.linprog(zarade, A_ub = conditions, b_ub = bounds, method='simplex')
    novi_res = [round(x) for x in res.x]
    print(novi_res)
    zarada = np.dot([-x for x in zarade], novi_res)
    print(zarada)
