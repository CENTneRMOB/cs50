#include <stdio.h>
#include <cs50.h>

int main(int argc, string argv[])
{
  for (int i = 1; i < argc; i++)
  {
    printf("%c", argv[i][0]);
  }
  printf("\n");
}