from scipy.optimize import dual_annealing, Bounds
import numpy as np

s =[173669, 275487, 1197613, 1549805, 502334, 217684, 1796841, 274708, 631252, 148665, 150254, 4784408, 344759, 440109, 4198037, 329673, 28602, 144173, 1461469, 187895, 369313, 959307, 1482335, 2772513, 1313997, 254845, 486167, 2667146, 264004, 297223, 94694, 1757457, 576203, 8577828, 498382, 8478177, 123575, 4062389, 3001419, 196884, 617991, 421056, 3017627, 131936, 1152730, 2676649, 656678, 4519834, 201919, 56080, 2142553, 326263, 8172117, 2304253, 4761871, 205387, 6148422, 414559, 2893305, 2158562, 465972, 304078, 1841018, 1915571]

def opt_f(x):
    f1 = 2**25
    f2 = 2**25
    for i in range(len(x)):
        if(round(x[i]) == 1):
            f1 -= s[i]
        if(round(x[i]) == 2):
            f2 -= s[i]
    if(f1<0 or f2<0):
        return 2**26
    return f1+f2

if __name__ == '__main__':
    x = np.ones(64)
    bounds = []
    for i in range(64):
        bounds.append((0,2))
    print(bounds)
    res = dual_annealing(opt_f, x0=x, initial_temp=2**26, maxfun=2**26 + 1,accept=1,bounds=bounds, maxiter=10000 )
    x_final = []
    for xi in res.x:
        x_final.append(round(xi))
    print(x_final)
    print(res.fun)

