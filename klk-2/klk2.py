import numpy as np
from scipy.optimize import minimize
import math as m
from numba import njit
from random import uniform, seed
import matplotlib.pyplot as plt

#uvid u kabinetu 88

bounds = [(1e-4, 5e-4), (0.1, 1.5), (5,15), (5,15), (20,30), (5,8), (55,75)]

x1 = [2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,7,7,7,7,10,10,10,10]
x2 = [0.0002, 0.0005, 0.0010, 0.0020, 0.0002, 0.0005, 0.0010, 0.0020, 0.0002, 0.0005, 0.0010, 0.0020, 0.0002, 0.0005, 0.0010, 0.0020, 0.0002, 0.0005, 0.0010, 0.0020, 0.0002, 0.0005, 0.0010, 0.0020]
y = [15.47, 15.86 ,15.98 ,16.00 ,16.33 ,16.93 ,17.13 ,17.19 ,16.98 ,17.78 ,18.06 ,18.17 ,17.40 ,18.42 ,18.78 ,18.93 ,17.85 ,19.28 ,19.80 ,20.04 , 18.00 , 20.05 , 20.80 , 21.17 ]

@njit()
def y_app(constants, x1, x2):
    if len(constants) != 7:
        raise IndexError
    A, B, C, D, E, F, G = constants
    
    value = -(A*x1) / m.pow(x2, B)
    value += C * m.log10(x1) + D
    value += E/(m.pow(x1, F))
    value -= G*x2

    return value

def y_opt(constants, x1s, x2s, ys):
    sum = 0
    for x1, x2, y in zip(x1s, x2s, ys):
        sum += m.pow(y - y_app(constants, x1,x2),2)

    return sum

if __name__ == '__main__':
    seed(10)
    fun_value = 10000
    for i in range(50):
        constants = [uniform(1e-4,5e-4), uniform(10, 15)*1e-2, uniform(5,15), uniform(5,15), uniform(20,30), uniform(5,8), uniform(55,75)]
        res = minimize(y_opt, constants, args = (x1,x2,y), method='Nelder-Mead', tol=1e-4, bounds=bounds) 
        if res.fun < fun_value:
            print('i = ', i)
            print(res.fun)
            print(res.x)
            fun_value = res.fun
            final_constants = res.x


    _x2 = 0.0002
    x1_pred = np.arange(2,10.01, 0.01)

    x1_tr = []
    y_tr = []

    for i, _ in enumerate(x2):
        if x2[i] == _x2:
            x1_tr.append(x1[i])
            y_tr.append(y[i])

    y_pred = [y_app(final_constants, _x1, _x2) for _x1 in x1_pred]

    plt.plot(x1_pred, y_pred, color='r')
    plt.plot(x1_tr, y_tr, 'bs')
    plt.savefig('klk2.png')



