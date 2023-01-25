import matplotlib.pyplot as plt

solutionsH= [];
solutionsR= [];
paretoptimalH= [];
paretoptimalR= [];
paretonumber = -1;
def read_data():
    global paretonumber,paretoptimalR,paretoptimalH,solutionsH,solutionsR;
    file= open('data.txt','r');
    row=0;
    for line in file:
        s=line.split(",");
        if(row==0):
            paretonumber = int (s[0]);
            row+=1;
            continue;
        elif( row==1):
            for x in s:
                values = x.split(";");
                paretoptimalH.append(float(values[0]));
                paretoptimalR.append(float(values[1]));
            row += 1;
        else:
            for x in s:
                values = x.split(";");
                solutionsH.append(float(values[0]));
                solutionsR.append(float(values[1]));
            row += 1;

    file.close();
def draw_graphic():
    fig1 = plt.figure();
    plt.scatter(solutionsH,solutionsR, color="blue",label = "Random points");
    plt.scatter(paretoptimalH,paretoptimalR, color="red", label = "Pareto frontier");

    plt.title("Pareto front")
    plt.xlabel('Magnetic field intensity');
    plt.ylabel('Resistence');
    plt.legend();
    plt.show();


def main():
    read_data();
    draw_graphic();


main();