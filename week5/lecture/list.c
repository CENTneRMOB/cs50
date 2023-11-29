#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(int argc, char *argv[])
{
    node *list = NULL;  // избавляемся от "garbage value если есть"

    for (int i = 1; i < argc; i++)
    {
        int number = atoi(argv[i]); // преобразуем строку в число

        node *n = malloc(sizeof(node)); //выделение памяти для элемента списка
        if (n == NULL)
        {
            return 1;
        }

        n->number = number; // значение number сохраняем в number элемента списка
        n->next = NULL; // значение указателя на следующий элемент обнуляем

        n->next = list; // значение указателя на следующий элемент приравниваем к указателю на текущий лист
        list = n; // делаем началом листа новый элемент(на уровне указателя)
    }

    node *ptr = list; // создаем новый указатель, указывающий на начало списка
    while (ptr != NULL)
    {
        printf("%i\n", ptr->number); // печать значения элемента списка
        ptr = ptr->next; // обновляем указатель - теперь он указывает на следующий элемент списка
    }

    ptr = list; // приравниваем значение птр к списку
    while (ptr != NULL)
    {
        node *next = ptr->next; // промежуточный указатель, который будет временно хранить указатель на следующий элемент
        free(ptr); // освобождаем память занятую указателем птр
        ptr = next; // приравниваем птр к временному значению
    }
}
