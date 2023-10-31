#include <cs50.h>
#include <stdio.h>

int get_checksum(long number);

int main(void) 
{
    long number = get_long("Number: ");
    
    if (number < 4000000000000) {
        printf("INVALID\n");
        return 0;
    }

    long check_for_ae = number / 10000000000000;
    long check_for_mc = number / 100000000000000;
    long check_for_visa1 = number / 1000000000000;
    long check_for_visa2 = number / 1000000000000000;

    if (check_for_ae == 34 || check_for_ae == 37)
    {
        int checksum = get_checksum(number);
        if (checksum % 10 == 0)
        {
            printf("AMEX\n");
            return 0;
        }

        printf("INVALID\n");
        return 0;
    }
    else if (check_for_mc == 51 || check_for_mc == 52 || check_for_mc == 53 || check_for_mc == 54 || check_for_mc == 55)
    {
        int checksum = get_checksum(number);
        if (checksum % 10 == 0)
        {
            printf("MASTERCARD\n");
            return 0;
        }

        printf("INVALID\n");
        return 0;
    }
    else if (check_for_visa1 == 4 || check_for_visa2 == 4)
    {
        int checksum = get_checksum(number);
        if (checksum % 10 == 0)
        {
            printf("VISA\n");
            return 0;
        }

        printf("INVALID\n");
        return 0;
    }

    printf("INVALID\n");
}

int get_checksum(long number)
{
    long dobled_sum = 0;
    long sum = 0;

    do
    {
        long reminder = number % 100;
        sum += reminder % 10;
        number = number / 100;
        long dobled_reminder = (reminder / 10) * 2;
        if (dobled_reminder >= 10)
        {
            dobled_sum += dobled_reminder / 10 + dobled_reminder % 10;
        }
        else
        {
            dobled_sum += dobled_reminder;
        }
    } while (number > 0);
    
    return (int) (dobled_sum + sum);
}

