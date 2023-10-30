#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    string message = get_string("Message: ");
    int length = strlen(message);
    int bits[length][BITS_IN_BYTE];

    for (int i = 0; i < length; i++)
    {
        int value = message[i];
        for (int j = BITS_IN_BYTE - 1; j >= 0; j--)
        {
            bits[i][j] = value % 2;
            value = value / 2;
        }

        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            print_bulb(bits[i][j]);
        }

        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
