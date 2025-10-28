#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char *keywords[] = {
    "int", "float", "char", "if", "else", "while", "for", "return", "void"};

int isKeyword(const char *word)
{
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++)
    {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=');
}

int isSymbol(char ch)
{
    return (ch == ';' || ch == ',' || ch == '(' || ch == ')' || ch == '{' || ch == '}');
}

void lexicalAnalyzer(FILE *fp)
{
    char ch;
    char token[100];
    int i = 0;

    while ((ch = fgetc(fp)) != EOF)
    {

        if (ch == ' ' || ch == '\t' || ch == '\n')
            continue;

        if (isalpha(ch) || ch == '_')
        {
            i = 0;
            while (isalnum(ch) || ch == '_')
            {
                token[i++] = ch;
                ch = fgetc(fp);
            }
            token[i] = '\0';
            ungetc(ch, fp);
            if (isKeyword(token))
                printf("Keyword: %s\n", token);
            else
                printf("Identifier: %s\n", token);
        }

        else if (isdigit(ch))
        {
            i = 0;
            while (isdigit(ch))
            {
                token[i++] = ch;
                ch = fgetc(fp);
            }
            token[i] = '\0';
            ungetc(ch, fp);
            printf("Number: %s\n", token);
        }

        else if (isOperator(ch))
        {
            printf("Operator: %c\n", ch);
        }

        else if (isSymbol(ch))
        {
            printf("Symbol: %c\n", ch);
        }

        else
        {
            printf("Unknown character: %c\n", ch);
        }
    }
}

int main()
{
    char filename[100];
    printf("Enter file name: ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    printf("Lexical Analysis Output:\n\n");
    lexicalAnalyzer(fp);

    fclose(fp);
    return 0;
}
