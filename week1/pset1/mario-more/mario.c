#include <cs50.h>
#include <stdio.h>

int print_string(int spaces, int hashtags);

int main(void) 
{
    int height;
    do
    {
      height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int i = 1; i <= height; i++)
    {
      int spaces = height - i;
      print_string(spaces, i);
    }
    
}

int print_string(int spaces, int hashtags)
{
    for (int i = 0; i < spaces; i++)
    {
      printf(" ");
    }
    for (int i = 0; i < hashtags; i++)
    {
      printf("#");
    }
    printf("  ");
    for (int i = 0; i < hashtags; i++)
    {
      printf("#");
    }
    printf("\n");
    return 0;
}