#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t decrypt_byte(uint64_t base, int exponent, int modular);


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Please enter a correct amount of arguments.\n");
        return 1;
    }

    FILE *file_to_decrypt = fopen(argv[1], "rb");

    if (file_to_decrypt == NULL)
    {
        printf("File not found.\n");
        return 2;
    }

    int d, n;
    FILE *key = fopen("private-key.txt", "r");

    if (key == NULL)
    {
        printf("Private key not found\n");
        return 3;
    }

    fscanf(key, "%i\n%i", &d, &n);
    fclose(key);

    char filename[256];
    sprintf(filename, "decrypted_%s", argv[1]);
    FILE *decrypted_file = fopen(filename, "wb");

    uint64_t buffer;
    uint8_t decrypted_buffer;

    while (fread(&buffer, sizeof(buffer), 1, file_to_decrypt) != 0)
    {
        decrypted_buffer = decrypt_byte(buffer, d, n) & 0xFF; // Only the first 8 bits are needed so we take that
        fwrite(&decrypted_buffer, sizeof(uint8_t), 1, decrypted_file);
    }

    fclose(file_to_decrypt);
    fclose(decrypted_file);

}

uint64_t decrypt_byte(uint64_t base, int exponent, int modular) // here we use binary exponentiation, as with other techniques the program can have overflow
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