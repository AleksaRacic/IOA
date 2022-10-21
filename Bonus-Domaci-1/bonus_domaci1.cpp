#define max_n 17

#include <stdio.h>
#include <math.h>
#include <climits>



int main(void){

    unsigned long long int a, b, c;
    int n = 1;
    unsigned long long int faktorijal = 1;

    printf("Resenja (a,b,c,n): \n");
    
    while(n < 21){

        for(a = 1; pow(a, n-1) < faktorijal; a++){
            for(b = 1; pow(b, n-1) <= faktorijal; b++){
                for(c=1; pow(c, n-1)<= faktorijal; c++){
                    if(faktorijal == pow(a,n-1) + pow(b, n-1) + pow(c, n-1)){
                        printf("(%d, %d, %d, %d)\n", a, b, c, n);
                    }
                }
            }
        }

        n++;
        faktorijal = faktorijal * n;
    }
    return 0;

}