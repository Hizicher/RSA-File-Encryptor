#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main(void)
{
    int e = 7;
    int q = 0;
    int d;
    int p = 0;

    int primes[170];
    primes[0] = 2;
    int current_primes = 1;
    int primes_needed[75]; // To store the primes between 500 - 1000
    int length_primes_needed = 0;
    int is_divisible;

    for (int num = 3; num < 1000; num++)
    {   
        is_divisible = 1;

        for (int i = 0; i < current_primes; i++)
        {
            if (num % primes[i] == 0)
            {
                is_divisible = 0;
                break;primes_needed[rand() % length_primes_needed];
            }
        }

        if (!is_divisible)
        {
            continue;
        }

        else
        {
            primes[current_primes] = num;
            current_primes++;
            
            if (num > 500)
            {
                primes_needed[length_primes_needed] = num;
                length_primes_needed++;
            }
        }
    }

    srand(time(NULL));
    p = primes_needed[rand() % length_primes_needed];
    q = p;

    while (p == q) // In order to prevent that p = q, p and q set to equal value delibaretely just so that we find another prime value for q
    {
        q = primes_needed[rand() % length_primes_needed];
    }

    int n = p * q;

    int r = (p - 1) * (q - 1);

    for (int i = 1; (e * i) % r != 1; i++)
    {
        if ((e * (i + 1)) % r == 1) // Until e's inverse is found d is incremented
        {
            d = i + 1;
            break;
        }
    }
    
    FILE *public = fopen("public-key.txt", "w");
    FILE *private = fopen("private-key.txt", "w");

    fprintf(public, "%i\n%i", e, n);
    fprintf(private, "%i\n%i", d, n);

    fclose(public);
    fclose(private);

    return 0;
}