#include <stdio.h>
#include <time.h>

const int sum = 777;
const int product = 777000000;

void zadatak_a()
{

    time_t t1, t2;
    unsigned long long function_call_count = 0;

    printf("ZADATAK A:\n\nResenja:\n");
    t1 = time(NULL);
    for (int x1 = 1; x1 < sum; ++x1)
    {
        for (int x2 = 1; x2 <= sum - x1; ++x2)
        {
            for (int x3 = 1; x3 <= sum - x1 - x2; ++x3)
            {
                for (int x4 = 1; x4 <= sum - x1 - x2 - x3; ++x4)
                {
                    function_call_count++;
                    if (x1 + x2 + x3 + x4 == sum && x1 * x2 * x3 * x4 == product)
                    {
                        printf("%0.2f %0.2f %0.2f %0.2f\n", x1/100.0, x2/100.0, x3/100.0, x4/100.0);
                    }
                }
            }
        }
    }
    t2 = time(NULL);
    printf("Vreme: %.5f\n", difftime((int)t2, (int)t1));
    printf("Broj poziva optimizacione funkcije: %llu \n", function_call_count);
}

void zadatak_b()
{

    time_t t1, t2;
    int x4;
    unsigned long long function_call_count = 0;

    printf("ZADATAK B:\n\nResenja:\n");
    t1 = time(NULL);
    for (int x1 = 1; x1 < sum; ++x1)
    {
        for (int x2 = 1; x2 <= sum - x1; ++x2)
        {
            for (int x3 = 1; x3 <= sum - x1 - x2; ++x3)
            {
                x4 = sum - x1 - x2 - x3;
                function_call_count++;
                if(x1*x2*x3*x4 == product) printf("%0.2f %0.2f %0.2f %0.2f\n", x1/100.0, x2/100.0, x3/100.0, x4/100.0);
            }
        }
    }
    t2 = time(NULL);
    printf("Vreme: %.5f\n", difftime((int)t2, (int)t1));
    printf("Broj poziva optimizacione funkcije: %llu \n", function_call_count);
}

int main(void)
{
    zadatak_a();
    zadatak_b();

    return 0;
}
