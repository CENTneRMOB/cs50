#include <stdio.h>

int main(void)
{
    int a = 28;
    int b = 50;
    int *c = &a;

    *c = 14;
    c = &b;
    *c = 25;

    printf("A info. address: %p, value: %i\n", &a, a);
    printf("B info. address: %p, value: %i\n", &b, b);
    printf("C info. address: %p, value: %p\n", &c, c);
}
