// #include <cs50.h>
#include <stdio.h>

int main(void)
// {
//     int n = 50;
//     int *p = &n;
//     printf("%p\n", *p);
// }
{
    char *s = "HI!";
    printf("%p\n", s); // output memory address
    printf("%s\n", s); // output string itself
    printf("%p\n", s);
    printf("%p\n", &s[0]); // output address equal previous
    printf("%p\n", &s[1]); // +1
    printf("%p\n", &s[2]); // +1

    printf("%s\n", s);
    printf("%s\n", s+1);
    printf("%s\n", s+2);
}