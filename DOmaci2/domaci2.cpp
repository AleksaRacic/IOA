#include <stdio.h>
#include <math.h>

const int num_holes = 12;

const double holes[num_holes][2] = {
    {62.0,58.4},
    {57.5, 56.0},
    {51.7, 56.0},
    {67.9, 19.6},
    {57.7, 42.1},
    {54.2, 29.1},
    {46.0, 45.1},
    {34.7, 45.1},
    {45.7, 25.1},
    {34.7, 26.4},
    {28.4, 31.7},
    {33.4, 60.5}
    };



int next_permutation(const int N, int *P){
    int s;
    int *first = &P[0];
    int* last = &P[N-1];
    int* k  = last - 1;
    int* l = last;


    while(k>first){
        if(*k<*(k+1)){
            break;
        }
        k--;
    }


    if(*k>*(k+1)) return 0;

    while(l>k){
        if(*l>*k){
            break;
        }
        l--;
    }

    s = *k;
    *k = *l;
    *l = s;

    first = k+1;

    while(first<last){
        s=*first;
        *first = *last;
        *last=s;

        first++;
        last--;
    }

    return 1;
}

double calculate_min_path(double **matrix, int *P, int num_dots){
    double sum = 0.0;
    for(int i = 1; i<num_dots; i++){
        sum+= matrix[P[i]][P[i-1]];
    }
    return sum;
}


int main(int argc, char *argv[]){
    int num_dots;
    if(argc<2) num_dots = 8;
    else num_dots = atoi(argv[1]);


    double **matrix = new double*[num_dots];
    for(int i = 0; i<num_dots; i++){
        matrix[i] = new double[num_dots];
        for(int j = 0; j < num_dots; j++){
            if(i!=j)
                matrix[i][j] = sqrt(pow(holes[i][0] - holes[j][0], 2) + pow(holes[i][1] - holes[j][1], 2));
        }
    }

    /*for(int i = 0; i<num_dots; i++){
        for(int j = 0; j < num_dots; j++){
            printf("%0.2f ", matrix[i][j]);
        }

        printf("\n");
    }*/
    
    int* P = new int[num_dots];
    int* final_P = new int[num_dots];
    double min_path = 1000000000000.0;
    double cur_path;

    for(int i = 0; i< num_dots; i++){
        P[i] = i;
    }



    do{
        cur_path = calculate_min_path(matrix, P, num_dots);

        if(cur_path < min_path){
            min_path = cur_path;
            for(int i = 0; i < num_dots; i++) final_P[i] = P[i];
        }

    }while(next_permutation(num_dots,P));

    printf("Resenje za %d rupa:\n\n", num_dots);

    printf("Duzina putanje: %0.2f\n", min_path);
    printf("Putanja: ");
    for(int i = 0; i< num_dots; i++){
        printf("%d ", final_P[i]+1);
    }

    printf("\n");


    return 0;
}