#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[]) //argc - количество вводимых аргументов, argv - массив вводимых элементов, где [0] элемент - название вызываемой программы
{
  if (argc == 2)
  {
    printf("hello, %s\n", argv[1]);
  }
  else
  {
    printf("hello, world\n"); // поведение по умолчанию
  }
}