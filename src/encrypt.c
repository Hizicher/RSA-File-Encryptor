#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t encrypt_byte(uint64_t base, int exponent, int modular);


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Please enter a correct amount of arguments.\n");
        return 1;
    }

    FILE *file_to_encrypt = fopen(argv[1], "rb");

    if (file_to_encrypt == NULL)
    {
        printf("File not found.\n");
        return 2;
    }

    int e, n;
    FILE *key = fopen("public-key.txt", "r");

    if (key == NULL)
    {
        printf("Public key not found\n");
        return 3;
    }
    
    fscanf(key, "%i\n%i", &e, &n);
    fclose(key);

    char filename[256];
    sprintf(filename, "encrypted_%s", argv[1]);
    FILE *encrypted_file = fopen(filename, "wb");

    uint8_t buffer;

    while (fread(&buffer, sizeof(buffer), 1, file_to_encrypt) != 0)
    {
        uint64_t encrypted_buffer = encrypt_byte(buffer, e, n);
        fwrite(&encrypted_buffer, sizeof(encrypted_buffer), 1, encrypted_file);
    }

    fclose(file_to_encrypt);
    fclose(encrypted_file);

}

uint64_t encrypt_byte(uint64_t base, int exponent, int modular) // here we use binary exponentiation, as with other techniques the program can have overflow
{
    unsigned long long int result;

    if (exponent % 2 == 1)
    {
        result = base % modular;
        exponent--;
        exponent /= 2;

        for (int i = 0; i < exponent; i++)
        {
            result *= ((base % modular) * (base % modular)) % modular;
            result %= modular;
        }

        uint64_t result_to_be_returned = (uint64_t)result;
        return result_to_be_returned;
    }


    result = 1;
    exponent /= 2;

    for (int i = 0; i < exponent; i++)
    {
        result *= ((base % modular) * (base % modular)) % modular;
        result %= modular;
    }


    uint64_t result_to_be_returned = (uint64_t)result;
    return result_to_be_returned;
}