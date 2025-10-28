#include <stdio.h>
#include <string.h>

int curr = 0;
int len = 0;
char input[100];

int E()
{
    int result;
    if (input[curr] == 'i')
    {
        curr++;
        result = Z();
        if (result == 1)
            return 1;
        else
            return -1;
    }
    return 1;
}

int Z()
{
    int result;
    if (input[curr] == '+' && input[curr + 1] == 'i')
    {
        curr = curr + 2;
        result = Z();
        if (result == 1)
        {
            return 1;
        }
    }
    return 1;
}

int main()
{
    printf("Enter input: \n");
    scanf("%s", input);
    len = strlen(input);

    int result = E();
    if (result == 1 && len == curr)
    {
        printf("\nString accepted\n");
    }
    else{
        printf("\nInput rejected\n");
    }
}
