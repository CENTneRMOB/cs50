#include <cs50.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Improper usage.\n");
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "r");

    // Check if file exists
    if (file == NULL)
    {
        printf("No such file found.\n");
        return 1;
    }

    uint8_t buffer[4];
    uint8_t signature[] = {37, 80, 68, 70};
    fread(buffer, 1, 4, file);
    fclose(file);

    for (int i = 0; i < 4; i++)
    {
        if(buffer[i] != signature[i])
        {
            printf("Likely not a PDF.\n");
            return 0;
        }
    }

    printf("Likely a PDF.\n");
    return 0;
}