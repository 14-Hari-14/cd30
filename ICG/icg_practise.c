#include <stdio.h>
#include <string.h>

void gen_code_operator(char *input, char operator, char *reg)
{
    int i = 0;
    int j = 0;
    char temp[100];

    while (input[i] != '\0')
    {
        if (input[i] == operator)
        {
            // assignment
            if (operator == '=')
            {
                printf("\n%c\t%c\t%c\t---\n", operator, input[i - 1], input[i + 1]);
                temp[j - 1] = input[i - 1];
            }
            else
            {
                printf("\n%c\t%c\t%c\t%c\n", operator, *reg, input[i - 1], input[i + 1]);
                temp[j - 1] = *reg;
                (*reg)--;
            }
            i += 2;
            continue;
        }
        temp[j] = input[i];
        i++;
        j++;
    }
    temp[j] = '\0';
    strcpy(input, temp);
}

void gen_code(char *input)
{
    char reg = 'Z';
    gen_code_operator(input, '/', &reg);
    gen_code_operator(input, '*', &reg);
    gen_code_operator(input, '+', &reg);
    gen_code_operator(input, '-', &reg);
    gen_code_operator(input, '=', &reg);
}

int main()
{
    char input[100];
    printf("Enter input: \n");
    scanf("%s", input);
    printf("\nOppr\tReg\tOp1\tOp2\t\n");
    printf("----------------------------\n");
    gen_code(input);
}