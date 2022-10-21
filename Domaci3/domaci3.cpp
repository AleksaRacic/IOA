#include <stdio.h>
#include <climits>

const int k = 8;
const int n = 10;


const int tabela_cena[10][10] =
    {{0, 374, 350, 223, 108, 178, 252, 285, 240, 356},
     {374, 0, 27, 166, 433, 199, 135, 95, 136, 17},
     {350, 27, 0, 41, 52, 821, 180, 201, 131, 247},
     {223, 166, 41, 0, 430, 47, 52, 84, 40, 155},
     {108, 433, 52, 430, 0, 453, 478, 344, 389, 423},
     {178, 199, 821, 47, 453, 0, 91, 37, 64, 181},
     {252, 135, 180, 52, 478, 91, 0, 25, 83, 117},
     {285, 95, 201, 84, 344, 37, 25, 0, 51, 42},
     {240, 136, 131, 40, 389, 64, 83, 51, 0, 118},
     {356, 17, 247, 155, 423, 181, 117, 42, 118, 0}};

void sequence_to_spanning_tree(int *P, int len, int *T)
{
    int i, j, q = 0;
    int n = len + 2;
    int *V = new int[n];

    for (i = 0; i < n; i++)
        V[i] = 0;

    for (i = 0; i < len; i++)
        V[P[i]] += 1;

    for (i = 0; i < len; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (V[j] == 0)
            {
                V[j] = -1;
                T[q++] = j + 1;
                T[q++] = P[i] + 1; //mozda +1
                V[P[i]]--;
                break;
            }
        }
    }
    j = 0;
    for (i = 0; i < n; i++)
    {
        if (V[i] == 0 && j == 0)
        {
            T[q++] = i + 1;
            j++;
        }
        else if (V[i] == 0 && j == 1)
        {
            T[q++] = i + 1;
            break;
        }
    }

    delete[] V;
}

int main(void)
{   

    int min_cena = INT_MAX;
    int cost;

    int *min_T = new int[2*(k+1)];
    int *T = new int[2*(k+1)];

    int *node_count = new int[n];

    int q;
    int *P = new int[k];
    for (int i = 0; i < k; i++)
    {
        P[i] = 0;
    }

    do
    {   
        cost = 0;

        for(int ii = 0; ii<n; ii++){
            node_count[ii] = 0;
        }

        sequence_to_spanning_tree(P, k, T);

        for(int j = 0; j < 2 * (k+1); j+=2){
            //printf("%d(%d) - %d(%d)  ", T[j], j, T[j+1], j+1);
            cost += tabela_cena[T[j]-1][T[j+1]-1];
            node_count[T[j]-1]++;
            node_count[T[j+1]-1]++;
        }

        for(int ii = 0; ii<n; ii++){
            if(node_count[ii] >= 4){
                cost += 250 * (node_count[ii]-3);
            }
        }


        if(cost < min_cena){
            min_cena = cost;
            for(int ii = 0; ii < 2*(k+1); ii++) min_T[ii] = T[ii];
        }

        q = k - 1;
        while (q >= 0)
        {
            P[q]++;
            if (P[q] == n)
            {
                P[q] = 0;
                q--;
            }
            else
                break;
        }

    } while (q >= 0);
    printf("Putanja: ");
    for(int j = 0; j < 2 * (k +1); j+=2){
        printf("%c %c - ", min_T[j]+64, min_T[j+1]+64);
    }

    printf("\n");
    printf("Cena: ");
    printf("%d\n", min_cena);

    delete[] P;
    delete[] min_T;
    delete[] T;
    delete[] node_count;

    return 0;
}