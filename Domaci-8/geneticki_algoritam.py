import numpy as np
from numba import njit
import random
import matplotlib.pyplot as plt

s =[173669, 275487, 1197613, 1549805, 502334, 217684, 1796841, 274708, 631252, 148665, 150254, 4784408, 344759, 440109, 4198037, 329673, 28602, 144173, 1461469, 187895, 369313, 959307, 1482335, 2772513, 1313997, 254845, 486167, 2667146, 264004, 297223, 94694, 1757457, 576203, 8577828, 498382, 8478177, 123575, 4062389, 3001419, 196884, 617991, 421056, 3017627, 131936, 1152730, 2676649, 656678, 4519834, 201919, 56080, 2142553, 326263, 8172117, 2304253, 4761871, 205387, 6148422, 414559, 2893305, 2158562, 465972, 304078, 1841018, 1915571]

K = 0.2
pop_num = 20000

#Rulet
def select_next_population1(F, population):
    fitness = np.array([F(p) for p in population])
    min_fitness = min(fitness)
    size = int(pop_num / 5)
    idx = np.random.choice(np.arange(pop_num), size=size, replace=True,
                           p=fitness/fitness.sum())
    population = population[idx]
    return population


#Decimacija
def select_next_population(F,population):
    fitness = [F(p) for p in population]
    k = list(zip(fitness, population))
    k.sort(key=lambda pair: pair[0])
    fitness, population = zip(*k)
    population = list(population[0:round(K*len(population))]) #uzima se  najbolja petina
    return population

def SAT_crossreference(population, k):
    pop_len = len(population)
    pop_size = len(population[0])
    for i in range(k-pop_len):
        cut_point = random.randint(0, pop_size)
        first = random.randint(0,pop_len-1)
        second = random.randint(0,pop_len-1)
        population.append([*population[first][0:cut_point], *population[second][cut_point:]])
    return population

def SAT_mutation(population, probability):
    for po in population[4000:]:
        if random.random() < probability:
            po[random.randint(0,63)] = random.randint(0,2)
    return population


@njit
def opt_f(x):
    s =[173669, 275487, 1197613, 1549805, 502334, 217684, 1796841, 274708, 631252, 148665, 150254, 4784408, 344759, 440109, 4198037, 329673, 28602, 144173, 1461469, 187895, 369313, 959307, 1482335, 2772513, 1313997, 254845, 486167, 2667146, 264004, 297223, 94694, 1757457, 576203, 8577828, 498382, 8478177, 123575, 4062389, 3001419, 196884, 617991, 421056, 3017627, 131936, 1152730, 2676649, 656678, 4519834, 201919, 56080, 2142553, 326263, 8172117, 2304253, 4761871, 205387, 6148422, 414559, 2893305, 2158562, 465972, 304078, 1841018, 1915571]

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

def find_min(F, population):
    fitness = [F(p) for p in population]
    return min(fitness)


def evolution_alg(F, N, pop_num, mut_prob = 0.1, num_points=1):
    cumulative_min = []
    population = np.random.randint(3,size=(pop_num,len(s)))
    rolling_min = find_min(F, population)
    cumulative_min.append(rolling_min)

    for i in range(N):
        print(i)
        population = select_next_population(F,population)
        population = SAT_crossreference(population, pop_num)
        population = SAT_mutation(population,mut_prob)
        rolling_min = min(rolling_min, find_min(F, population))
        cumulative_min.append(rolling_min)
    
    res = dict()
    res['cmin'] = cumulative_min
    fitness = [F(p) for p in population]
    k = list(zip(fitness, population))
    k.sort(key=lambda pair: pair[0])
    fitness, population = zip(*k)
    res['x'] = population[0]
    res['f'] = cumulative_min[-1]
    return res
        
    

if __name__ == '__main__':
    cmins = []
    xs = []
    fs =[]
    f_min = 10000000
    x_min = []
    for i in range(20):
        print('POKRETANJE ', i)
        res = evolution_alg(opt_f, 50, pop_num, 0.20, 2)
        print(res)
        cmins.append(res['cmin'])
        xs.append(res['x'])
        fs.append(res['f'])
        if f_min > res['f']:
            f_min = res['f']
            x_min = res['x']
    
    print("Best solution")
    print(f_min)
    print(x_min)

    
    x=np.arange(1,52,1)
    fig1= plt.figure()
    for i in range(20):
        plt.plot(np.log10(x),np.log10(cmins[i]))
    plt.title("Kumulativni minimum")
    plt.xlabel('Iteracije')
    plt.ylabel('Kumulativni minimum')
    plt.show()
    plt.savefig('cum_min', format = 'png')

    average_opt = []
    for i in range(len(cmins[0])):
        sum = 0
        for j in range(len(cmins)):
            sum += cmins[j][i]
        average_opt.append(sum/len(cmins))

    fig2=plt.figure()
    plt.title("Srednje najbolje pronadjeno resenje")
    plt.plot(np.log10(x),np.log10(average_opt))
    plt.xlabel('Iteracije')
    plt.ylabel('Srednji kumulativni minimum')
    plt.show()
    plt.savefig('avg_cum_min', format='png')