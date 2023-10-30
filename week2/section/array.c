#include <stdio.h>
#include <cs50.h>

int main(void)
{
  int length;
  do
  {
    length = get_int("Pick length of array: ");
  }
  while (length < 1);

  const int start = 1;
  int array[length];
  array[0] = start;

  printf("%i\n", array[0]);
  for (int i = 1; i < length; i++)
  {
    array[i] = array[i - 1] * 2;
    printf("%i\n", array[i]);
  }
}