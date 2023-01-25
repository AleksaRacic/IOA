import math
import numpy as np
import random
from scipy.optimize import minimize, Bounds
import matplotlib.pyplot as plt

sateliti = [[9.353956971444877e+06,	2.118990698587988e+07,	1.982601765067424e+07,	8.269561714563388e+06],
[1.241312016061606e+07,	3.927317122951025e+06,	3.567263619968160e+06,	2.272043407954935e+07],
[2.155077673436540e+07,	1.554291038208530e+07,	1.732690668817735e+07,	1.101881415061893e+07],
[6.953977405819632e-02,	6.796520885661889e-02,	6.769215215591819e-02,	7.501668358266193e-02],
[6.953977e-02,	6.796521e-02,	6.769215e-02,	7.501668e-02]]

c0 = 299_792_458

def opt_f_exact(xyz):
    sum = 0
    for i in range(4):
        exp = pow(xyz[0] - sateliti[0][i],2) + pow(xyz[1] - sateliti[1][i],2) + pow(xyz[2] - sateliti[2][i],2)
        exp = exp / pow(c0 * sateliti[3][i],2)
        exp = exp - 1
        exp = pow(exp, 2)
        sum += exp
    return math.sqrt(sum)

def opt_f_error(xyz):
    sum = 0
    for i in range(4):
        exp = pow(xyz[0] - sateliti[0][i],2) + pow(xyz[1] - sateliti[1][i],2) + pow(xyz[2] - sateliti[2][i],2)
        exp = exp / pow(c0 * sateliti[4][i],2)
        exp = exp - 1
        exp = pow(exp, 2)
        sum += exp
    return math.sqrt(sum)

def calculate_distance(xyz1, xyz2):
    sum = pow(xyz1[0] - xyz2[0], 2) + pow(xyz1[1] - xyz2[1], 2) + pow(xyz1[2] - xyz2[2], 2)
    return math.sqrt(sum)

if __name__ == "__main__":
    random.seed(12)
    weights = [random.random()*8e7 - 4e7 for _ in range(3)]

    res_exact = minimize(opt_f_exact, weights, method='Nelder-Mead', tol=1e-4, bounds=Bounds(-4e7,4e7))
    print('==============A: tacno vreme ============')
    print(res_exact.fun)
    print(res_exact.x)


    random.seed(12)
    weights = [random.random()*8e7 - 4e7 for _ in range(3)]

    res_err = minimize(opt_f_error, weights, method='Nelder-Mead', tol=1e-4, bounds=Bounds(-4e7,4e7))
    print('==============B: vreme sa greskom ============')
    print(res_err.fun)
    print(res_err.x)

    print()
    print("Distanca: ", calculate_distance(res_exact.x, res_err.x))



