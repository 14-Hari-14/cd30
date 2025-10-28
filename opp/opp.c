#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int top = -1;
char input[100];
char stack[100];
int len = -1;
int input_ptr = 0;

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

void print_details(const char *action)
{
    printf("$");
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
        if (
            stack[top - 2] == 'E' && (stack[top - 1] == '+' || stack[top - 1] == '*') && stack[top] == 'E')
        {
            handle = 3;
        }
    }

    if (top >= 0 && stack[top] == 'i' && handle == 0)
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
    printf("Enter input: \n");
    scanf("%s", input);
    len = strlen(input);
    top++;
    stack[top] = '$';
    printf("\nSTACK\t\tINPUT\t\t\tACTION\n");
    printf("--------------------------------------------\n");
    while (1)
    {
        char Ts = get_top_terminal();
        char Ti = input[input_ptr];

        // case1 : accept or reject
        if (Ts == '$' && Ti == '$')
        {
            if (top == 1 && stack[top] == 'E')
            {
                print_details("ACCEPT");
                printf("\nInput accepted\n");
                break;
            }
            else
            {
                printf("Rejected");
                break;
            }
        }

        // case2 : shift or reduce

        int Ts_idx = get_precedence(Ts);
        int Ti_idx = get_precedence(Ti);

        if (Ts == -1 || Ti == -1)
        {
            printf("\nInvalid variable\n");
            break;
        }

        int relation = precedence_table[Ts_idx][Ti_idx];

        // shift
        if (relation == 0)
        {
            top++;
            stack[top] = Ti;
            input_ptr++;
            print_details("SHIFT");
        }

        // reduce
        else if (relation == 1)
        {
            int reduced = 1;
            while (reduced)
            {
                reduced = check_and_reduce(); // if reduction happened it will be 1 else 0

                if (reduced == 0)
                {
                    printf("\nInvalid Reduction not possible\n");
                    break;
                }

                // recalculate top terminal after reduction
                Ts = get_top_terminal();
                Ts_idx = get_precedence(Ts);

                // check precedence between new Ts and existing Ti
                if (Ts_idx != -1 && Ti_idx != -1)
                {
                    relation = precedence_table[Ts_idx][Ti_idx];
                }

                // if further reduction is possible then continue else break
                if (relation != 1)
                {
                    break;
                }
            }
        }
        // case3: reject due to error
        else
        {
            printf("\nReject due to some error\n");
            break;
        }
    }
    return 0;
}

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

// char inp[100];
// char stack[100];
// int len, top = -1;
// int input_ptr = 0;

// int precedence_table[6][6] = {
//     {3, 1, 1, 3, 1, 1},
//     {0, 1, 0, 0, 1, 1},
//     {0, 1, 1, 0, 1, 1},
//     {0, 0, 0, 0, 2, 3},
//     {3, 1, 1, 3, 1, 1},
//     {0, 0, 0, 0, 3, 2}};

// int get_precedence_index(char c)
// {
//     if (c == 'i')
//         return 0;
//     if (c == '+')
//         return 1;
//     if (c == '*')
//         return 2;
//     if (c == '(')
//         return 3;
//     if (c == ')')
//         return 4;
//     if (c == '$')
//         return 5;
//     return -1;
// }

// char get_top_terminal()
// {
//     for (int i = top; i >= 0; i--)
//     {
//         if (stack[i] != 'E')
//         {
//             return stack[i];
//         }
//     }
//     return '$';
// }

// void print_details(const char *action)
// {
//     printf("$");
//     for (int i = 0; i <= top; i++)
//         printf("%c", stack[i]);
//     printf("\t\t");
//     for (int i = input_ptr; i < len; i++)
//         printf("%c", inp[i]);
//     printf("$\t\t%s\n", action);
// }

// int check_and_reduce()
// {
//     // reduce function returns 1 if reduction happened else 0
//     int handle_len = 0;

//     // Check for handle E+E, E*E, (E) (Length 3)
//     if (top >= 2)
//     {
//         if ((stack[top - 2] == 'E' && (stack[top - 1] == '+' || stack[top - 1] == '*') && stack[top] == 'E') ||
//             (stack[top - 2] == '(' && stack[top - 1] == 'E' && stack[top] == ')'))
//         {
//             handle_len = 3;
//         }
//     }

//     // Check for handle i (Length 1)
//     if (handle_len == 0 && top >= 0 && stack[top] == 'i')
//     {
//         handle_len = 1;
//     }

//     if (handle_len > 0)
//     {
//         // Reduction successful: pop the handle, push 'E'
//         top -= (handle_len - 1); // Top moves to the spot where 'E' will be placed
//         stack[top] = 'E';        // Push 'E'
//         print_details("REDUCE");
//         return 1;
//     }
//     return 0;
// }

// int main()
// {
//     printf("Enter input string (append with $ for end-of-input):\n");
//     scanf("%s", inp);
//     len = strlen(inp);
//     top++;
//     stack[top] = '$';
//     printf("\n%-16s%-16s%-s\n", "Stack", "Input", "Action");
//     printf("----------------------------------------------------------\n");

//     while (1)
//     {
//         char Ts = get_top_terminal();
//         char Ti = inp[input_ptr];

//         if (Ts == '$' && Ti == '$')
//         {
//             if (top == 1 && stack[top] == 'E')
//             {
//                 print_details("ACCEPT");
//                 printf("\nResult: Accepted.\n");
//             }
//             else
//             {
//                 printf("\nResult: Rejected. Stack: $%s\n", stack);
//             }
//             break;
//         }

//         int Ts_idx = get_precedence_index(Ts);
//         int Ti_idx = get_precedence_index(Ti);

//         if (Ts_idx == -1 || Ti_idx == -1)
//         {
//             print_details("ERROR: Invalid Symbol");
//             printf("\nResult: Rejected (Invalid Symbol).\n");
//             break;
//         }

//         int relation = precedence_table[Ts_idx][Ti_idx];

//         if (relation == 0) //|| relation == 2)
//         {
//             top++;
//             stack[top] = Ti;
//             input_ptr++;
//             print_details("SHIFT");
//         }
//         else if (relation == 1)
//         {
//             int reduced = 1;
//             while (reduced)
//             {
//                 reduced = check_and_reduce();

//                 if (reduced == 0)
//                 {
//                     print_details("ERROR: No valid reduction");
//                     printf("\nResult: Rejected (No valid reduction).\n");
//                     return 0;
//                 }

//                 Ts = get_top_terminal();
//                 Ts_idx = get_precedence_index(Ts);

//                 if (Ts_idx != -1 && Ti_idx != -1)
//                 {
//                     relation = precedence_table[Ts_idx][Ti_idx];
//                 }

//                 if (relation != 1)
//                 {
//                     break;
//                 }
//             }
//         }
//         else
//         {
//             print_details("ERROR: Precedence Conflict");
//             printf("\nResult: Rejected (Precedence Conflict).\n");
//             break;
//         }
//     }
//     return 0;
// }