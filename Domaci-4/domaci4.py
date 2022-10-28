from unicodedata import name
import numpy as np
from math import cos, e, pi
import matplotlib.pyplot as plt

def Fs_zadatak(delta):
    return abs(Fs(delta, 5, 20 * pi, pi/4, 1/20))

def Fs(delta, n, beta, theta, d):
    fs_result = complex(0.0,0.0)
    fi = delta + beta * d * cos(theta)

    for k in range(n):
        fs_result += pow(e, complex(0.0, -k * fi))
    
    return fs_result

def parabola_approximation(x1, x2, x3, y1, y2, y3):
    matrix = np.matrix([[pow(x1,2), x1, 1], [pow(x2,2), x2, 1], [pow(x3,2), x3, 1]])
    #print("matrica", matrix)
    y_matrix = np.matrix([[y1], [y2], [y3]])
    return np.linalg.inv(matrix) * y_matrix

def brent_max(func, starting_points, error):
    points = np.sort(starting_points)

    while(points[1] - points[0] > error or points[2] - points[1] > error):
        g = parabola_approximation(points[0],points[1],points[2],Fs_zadatak(points[0]), Fs_zadatak(points[1]), Fs_zadatak(points[2]))
        min = -(g.item(1,0))/(2*g.item(0,0))
        #print("points", points)
        ys = [Fs_zadatak(x) for x in points]
        index = np.argmin(ys)
        points[index] = min
        points.sort()
        #print("F(points)", ys)
    
    return points[1]





if __name__ == "__main__":

    deltas = np.linspace(0, 2*pi, 100)

    Fss = [Fs_zadatak(delta) for delta in deltas]

    plt.plot(deltas, Fss)
    plt.title = "Fs(x)"
    plt.xlabel("delta")
    plt.ylabel("|Fs(delta)|")
    plt.savefig("Fs.png")
    print("Pocetne tacke: 3.5, 4.0, 4.5")
    x_max = brent_max(Fs_zadatak, [3.5,4.0,4.5], 10e-7)
    print("Maximum funkcije: ")
    print("delta: ", x_max, "|Fs(delta)|: ", Fs_zadatak(x_max))