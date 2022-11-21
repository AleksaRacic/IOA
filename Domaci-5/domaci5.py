import math
import numpy as np
import random
from scipy.optimize import minimize, Bounds
import matplotlib.pyplot as plt

def y_training(x):
    return\
        -1 +\
            2*(math.pow(math.sin(math.pi*(x+1)/2), 4)\
                + (1/4)*math.pow(((math.pi/2)\
                    *math.pow((1-abs(math.cos((math.pi/4)*(x+1)))),4)),4))

def activation(x):
    return math.tanh(x)

def y_out(x, weights):
    if len(weights) != 16:
        raise IndexError
    y = 0
    for i in range(5):
        y += weights[i+10] * activation(weights[i]*x + weights[i+5])
    return y + weights[15]

def opt_f(weights):
    x = np.arange(-1, 1.01, 0.02)
    sum = 0
    cnt = 0
    for x_in in x:
        cnt += 1
        sum += math.pow(y_out(x_in, weights) - y_training(x_in),2)
    return sum/cnt

if __name__ == "__main__":
    random.seed(10)
    weights = [random.random()*10 - 5 for _ in range(16)]
    res = minimize(opt_f, weights, method='Nelder-Mead', tol=1e-7, bounds=Bounds(-5,5), options={'maxiter': 150000, 'disp': True})
    
    x = np.arange(-1, 1.01, 0.02)
    Y_training = [y_training(x_in) for x_in in x]
    Y_out = [y_out(x_in, res.x) for x_in in x]
    plt.plot(x, Y_training, color='red', label='y_training')
    plt.plot(x, Y_out, color='blue', label='y_out')
    plt.show()
    plt.savefig('domaci5.png')


