#include <stdio.h>

int main(void)
{
    int a = 28; // a - random address, value 28
    int b = 50; // b - random address, value 50
    int *c = &a; // pointer c point to address of a(value stored at a)

    *c = 14; // because of previous, GO TO c pointer(in this case address of a) and store value 14(now a value is 14)
    c = &b; // store address of b to value of c, so now c point to address of b(and value of c = address of b)
    *c = 25; //GO TO pointer c, witch point to b and set value to 25(now b = 25)

    printf("A info. address: %p, value: %i\n", &a, a);
    printf("B info. address: %p, value: %i\n", &b, b);
    printf("C info. address: %p, value: %p\n", &c, c);
}
