#include <cs50.h>
#include <stdio.h>

int get_factorial(int n);

int main(void)
{
    int number = get_int("Factorial: ");

    int factorial = get_factorial(number);

    printf("%i\n", factorial);
}

int get_factorial(int n)
{
    if (n == 1)
    {
        return 1;
    }

    return n * get_factorial(n - 1);
}