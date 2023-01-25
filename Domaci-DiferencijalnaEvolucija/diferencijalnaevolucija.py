import numpy as np
import random as random
F = 0.8
CR = 0.9
dimension = 6
N = 20
R0 = 15
xmin = -10
xmax = 10
PopulationSize = 60
S = [2.424595205726587e-01, 1.737226395065819e-01, 1.315612759386036e-01,
	1.022985539042393e-01, 7.905975891960761e-02, 5.717509542148174e-02,
	3.155886625106896e-02, -6.242228581847679e-03, -6.565183775481365e-02,
	-8.482380513926287e-02, -1.828677714588237e-02, 3.632382803076845e-02,
	7.654845872485493e-02, 1.152250132891757e-01, 1.631742367154961e-01,
	2.358469152696193e-01, 3.650430801728451e-01, 5.816044173713664e-01,
	5.827732223753571e-01, 3.686942505423780e-01];

xoptimal=[];
foptimal=(np.double)(100);
isset=False;
def init_pop():
	x= np.zeros((PopulationSize,dimension));
	for i in range (PopulationSize):
		for j in range(dimension):
			x[i][j]= np.random.uniform(xmin,xmax);
	return x;

def get_xy(i):
	x=R0*np.cos(2*np.pi*i/N);
	y = R0 * np.sin(2 * np.pi * i / N);
	return [x,y];

def calculate_signal( xiyi,xkyk,Ak):
	rk = np.sqrt(pow(xiyi[0] - xkyk[0], 2) + pow(xiyi[1] - xkyk[1], 2));
	return Ak / rk;

def check_coords(x):
	return (np.sqrt(pow(x[0],2)+pow(x[1],2))<R0) and (np.sqrt(pow(x[2],2)+pow(x[3],2))<R0);

def opt_function(x):
	fopt = 0;
	if(check_coords(x)):
		for i in range (N):
			xiyi=get_xy(i);
			signal =0;

			xkyk = [x[0], x[1]];
			Ak = [x[4]];
			signal+= calculate_signal(xiyi,xkyk,Ak);
			xkyk = [x[2], x[3]];
			Ak = [x[5]];
			signal += calculate_signal(xiyi, xkyk, Ak);

			signal-=S[i];
			signal= pow(signal,2);
			fopt+=signal;
	else: fopt=100;
	return fopt;

def DifferentialEvolution():
	global foptimal;
	global xoptimal;
	global isset;
	while(foptimal>1e-14):
		x=init_pop();
		"""minimum=-1;
			for xs in x:
			localmin=opt_function(xs);
			if(localmin<minimum or minimum==-1):
				minimum=localmin;
			if(not isset):
				foptimal=minimum;
				xoptimal=xs;
				isset=True;"""
		y=np.zeros((PopulationSize,dimension));
		for i in range (PopulationSize):
			a = random.randint(0,PopulationSize-1);
			while(a==i): a = random.randint(0,PopulationSize-1);
			b = np.random.randint(0,PopulationSize-1);
			while (b == i or b==a): b = random.randint(0, PopulationSize - 1);
			c= random.randint(0,PopulationSize-1);
			while (c == i or c == a or c==b): c = random.randint(0, PopulationSize - 1);
			z= x[a] + F*(x[b] - x[c]);
			#Crossover
			R = np.random.randint(1,dimension);
			r=[];

			for j in range (dimension):
				r.append(np.random.uniform(0,1));
				if(r[j]<CR or j==R):
					y[i][j]=z[j];
				else: y[i][j]=x[i][j];

			fyi=opt_function(y[i]);
			fxi=opt_function(x[i]);
			if(fyi<fxi):
				x[i]=y[i];
			fopt= opt_function(x[i]);
			lastfoptimal= foptimal;
			if(not isset):
				foptimal=fopt;
				xoptimal=x[i];
				isset=True;
			else:
				if(foptimal>fopt):
					foptimal=fopt;
					xoptimal=x[i];

DifferentialEvolution();
print("x = (",end='');
for i in range(dimension):
	if(i!=dimension-1):
		print(xoptimal[i],end=", ");
	else:print(xoptimal[i],end=")\n");

print("Value of optimizing function is ",foptimal);
