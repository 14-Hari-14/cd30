#include <stdio.h>
#include <string.h>

char inp[100], stack[100];
int len, top = -1;

void print_details(int ind, const char *action)
{
    printf("$");
    for (int i = 0; i <= top; i++)
        printf("%c", stack[i]);

    printf("\t\t");

    for (int i = ind; i < len; i++)
        printf("%c", inp[i]);

    printf("$\t\t%s\n", action);
}

void check_for_reduce(int i)
{
    int flag = 1;

    while (flag)
    {
        flag = 0;

        if (top >= 2 && stack[top - 2] == 'S' && stack[top - 1] == '+' && stack[top] == 'S')
        {
            print_details(i + 1, "REDUCE: S -> S+S");
            stack[top - 2] = 'S';
            top -= 2;
            flag = 1;
        }
        else if (top >= 2 && stack[top - 2] == 'S' && stack[top - 1] == '-' && stack[top] == 'S')
        {
            print_details(i + 1, "REDUCE: S -> S-S");
            stack[top - 2] = 'S';
            top -= 2;
            flag = 1;
        }
        else if (top >= 2 && stack[top - 2] == '(' && stack[top - 1] == 'S' && stack[top] == ')')
        {
            print_details(i + 1, "REDUCE: S -> (S)");
            stack[top - 2] = 'S';
            top -= 2;
            flag = 1;
        }
        else if (top >= 0 && stack[top] == 'i')
        {
            print_details(i + 1, "REDUCE: S -> i");
            stack[top] = 'S';
            flag = 1;
        }
    }
}

int main()
{
    printf("Enter input string:\n");
    scanf("%s", inp);
    len = strlen(inp);

    printf("\n%-16s%-16s%-s\n", "Stack", "Input", "Action");
    printf("----------------------------------------------------------\n");

    for (int i = 0; i < len; i++)
    {
        top++;
        stack[top] = inp[i];
        print_details(i + 1, "SHIFT");
        check_for_reduce(i);
    }

    if (top == 0 && stack[0] == 'S')
    {
        printf("%-16s%-16c%-s\n", "$S", '$', "ACCEPT");
        printf("\nResult: Accepted.\n");
    }
    else
    {
        printf("\nResult: Rejected.\n");
    }
    return 0;
}