#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int top = -1;
int len = -1;
int input_ptr = 0;
char input[100];
char stack[100];

int precedence_table[4][4] = {
    {3, 1, 1, 1},
    {0, 1, 0, 1},
    {0, 1, 1, 1},
    {0, 0, 0, 2}};

int get_precedence(char c)
{
    switch (c)
    {
    case 'i':
        return 0;
    case '+':
        return 1;
    case '*':
        return 2;
    case '$':
        return 3;
    default:
        return -1;
    }
}

int get_top_terminal()
{
    for (int i = top; i >= 0; i--)
    {
        if (stack[i] != 'E')
        {
            return stack[i];
        }
    }
    return '$';
}

int print_details(char *action)
{
    for (int i = 0; i <= top; i++)
    {
        printf("%c", stack[i]);
    }
    printf("\t\t");
    for (int i = input_ptr; i < len; i++)
    {
        printf("%c", input[i]);
    }
    printf("\t\t");
    printf("%s\n", action);
}

int check_and_reduce()
{
    int handle = 0;

    if (top >= 2)
    {
        if (stack[top - 2] == 'E' && (stack[top - 1] == '+' || stack[top - 1] == '*') && stack[top] == 'E')
        {
            handle = 3;
        }
    }

    if (top >= 0 && handle == 0 && stack[top] == 'i')
    {
        handle = 1;
    }

    if (handle > 0)
    {
        top -= (handle - 1);
        stack[top] = 'E';
        print_details("REDUCE");
        return 1;
    }
    return 0;
}

int main()
{
    printf("Enter input with $ at the end:\n");
    scanf("%s", input);
    len = strlen(input);

    top++;
    stack[top] = '$';

    printf("\nSTACK\t\tINPUT\tACTION\n");
    printf("----------------------------------------------\n");

    while (1)
    {
        char Ts = get_top_terminal();
        char Ti = input[input_ptr];

        if (Ts == '$' && Ti == '$')
        {
            // printf("\n%d, %c\n", top, stack[top]);
            if (top == 1 && stack[top] == 'E')
            {
                print_details("ACCEPTED");
                printf("\nAccepted\n");
                break;
            }
            else
            {
                printf("\nInvalid sequence\n");
                break;
            }
        }

        int Ts_idx = get_precedence(Ts);
        int Ti_idx = get_precedence(Ti);

        if (Ts_idx == -1 || Ti_idx == -1)
        {
            printf("Invalid symbol");
            break;
        }

        int relation = precedence_table[Ts_idx][Ti_idx];

        if (relation == 0)
        {
            top++;
            stack[top] = Ti;
            input_ptr++;
            print_details("SHIFT");
        }
        else if (relation == 1)
        {
            int reduced = 1;
            while (reduced)
            {
                reduced = check_and_reduce();

                if (reduced == 0)
                {
                    printf("Invalid reduction");
                    break;
                }

                Ts = get_top_terminal();
                Ts_idx = get_precedence(Ts);

                if (Ts_idx != -1 && Ti_idx != -1)
                {
                    relation = precedence_table[Ts_idx][Ti_idx];
                }

                if (relation != 1)
                {
                    break;
                }
            }
        }
        else
        {
            printf("\nERROR\n");
            break;
        }
    }
    return 0;
}