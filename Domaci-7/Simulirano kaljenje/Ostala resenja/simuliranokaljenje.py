import matplotlib.pyplot as plt
import numpy as np
N=20;
MaxIterations=1000000;
xoptimal=[];
otpimal_optvalue=-1;
optvalues= np.zeros((N,MaxIterations));
average_opt= [];
def read_data():
    file= open('../data.txt','r');
    row=0;
    i=0;
    optvaluesfinished=False;
    averagevaluesstarted=False;
    for line in file:
        s=line.split(",");
        if(row==0 or row==2 or row==4):
            row+=1;
            continue;
        if(row==1):
            for x in s:
              xoptimal.append((int)(x));
        elif(row==3):
            otpimal_optvalue=(int)(s[0]);
        elif(not optvaluesfinished):
            j=0;
            for optval in s:
                optvalues[i][j]=(int)(optval);
                j+=1;
            i+=1;
            if(i==N):
                optvaluesfinished=True;
                i=0;
        elif(not averagevaluesstarted):
            averagevaluesstarted=True;
            continue;
        else:
            j=0;
            for averageval in s:
                average_opt.append((int)(averageval));
                j+=1;
            i+=1;
        row += 1;
    file.close();
    return otpimal_optvalue;

def draw_graphic():
    x=np.arange(1,MaxIterations+1,1);
    fig1= plt.figure();
    for i in range(N):
        #run= i+1;
        #r= "run "+ str(run);
        plt.plot(np.log10(x),np.log10(optvalues[i]));
    plt.title("Kumulativni minimum")
    plt.xlabel('iterations');
    plt.ylabel('cumulative minimum of optimizing function');
    #plt.legend(loc='center');
    plt.show();

    fig2=plt.figure();
    plt.title("Srednje najbolje pronadjeno resenje");
    plt.plot(np.log10(x),np.log10(average_opt));
    plt.xlabel('iterations');
    plt.ylabel('average cumulative minimum of optimizing function');
    plt.show();

def main():
    otpimal_optvalue=read_data();
    draw_graphic();
    print("x=(",end="");
    i=0;
    for x in  xoptimal:
        if(i!=len(xoptimal)-1): print(x,end=",");
        else: print(x,end=")\n");
        i+=1;
    print("Minimal value of optimizing function is ",otpimal_optvalue);


main();