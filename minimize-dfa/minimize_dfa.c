#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

int findalpha(char inp, int a, char alphabet[a])
{
    for (int i = 0; i < a; i++)
    {
        if (alphabet[i] == inp)
        {
            return i;
        }
    }
    return -1;
}

int findStateIndex(char ch, int n, char states[n])
{
    for (int i = 0; i < n; i++)
    {
        if (states[i] == ch)
            return i;
    }
    return -1;
}

void reset(int n, int table[n][n])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            table[i][j] = 0;
}

int isFinal(int i, int f, int final[f])
{
    for (int j = 0; j < f; j++)
        if (final[j] == i)
            return 1;
    return 0;
}

void printTable(int n, int table[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", table[i][j]);
        printf("\n");
    }
}

void merge(int n, int empty[n][n], int i, int j)
{
    int flag = 0;
    for (int k = 0; k < n; k++)
        if (empty[i][k] && empty[j][k])
            flag = 1;

    if (flag)
    {
        for (int k = 0; k < n; k++)
        {
            if (empty[j][k])
            {
                empty[i][k] = 1;
                empty[j][k] = 0;
            }
        }
    }
}

int main()
{
    int n, a, from, to, index;
    char s1, s2, symbol;

    printf("Enter number of states: ");
    scanf("%d", &n);

    char states[n];
    printf("Enter state names (e.g., ABC): ");
    scanf("%s", states);

    printf("Enter size of alphabet: ");
    scanf("%d", &a);

    char alphabet[a];
    printf("Enter alphabet characters (e.g., ab): ");
    scanf("%s", alphabet);

    int transition[n][a];
    int table[n][n];
    reset(n, table);

    int f;
    printf("Enter number of final states: ");
    scanf("%d", &f);

    char finalStates[f];
    int finalIndexes[f];
    printf("Enter final state names (e.g., B C): ");
    for (int i = 0; i < f; i++)
    {
        scanf(" %c", &finalStates[i]);
        finalIndexes[i] = findStateIndex(finalStates[i], n, states);
    }

    int t;
    printf("Enter number of transitions: ");
    scanf("%d", &t);

    printf("Enter transitions (format: A a B):\n");
    for (int i = 0; i < t; i++)
    {
        scanf(" %c %c %c", &s1, &symbol, &s2);
        from = findStateIndex(s1, n, states);
        to = findStateIndex(s2, n, states);
        index = findalpha(symbol, a, alphabet);
        transition[from][index] = to;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if ((isFinal(i, f, finalIndexes) && !isFinal(j, f, finalIndexes)) ||
                (isFinal(j, f, finalIndexes) && !isFinal(i, f, finalIndexes)))
            {
                table[i][j] = 1;
            }
        }
    }

    printf("\nAfter marking initial distinguishable pairs:\n");
    printTable(n, table);

    int out1, out2, changed = 1;
    while (changed)
    {
        changed = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (table[i][j])
                    continue;
                for (int k = 0; k < a; k++)
                {
                    out1 = transition[i][k];
                    out2 = transition[j][k];
                    if (table[out1][out2] || table[out2][out1])
                    {
                        table[i][j] = 1;
                        changed = 1;
                        break;
                    }
                }
            }
        }
    }

    printf("\nFinal Myhill-Nerode Table:\n");
    printTable(n, table);

    int groups[n][n];
    int flags[n];
    for (int i = 0; i < n; i++)
    {
        flags[i] = 0;
        for (int j = 0; j < n; j++)
        {
            groups[i][j] = 0;
        }
    }
    int g = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (table[i][j] == 0)
            {
                int found = 0;
                for (int m = 0; m < g; m++)
                {
                    if (groups[m][i] || groups[m][j])
                    {
                        groups[m][i] = 1;
                        groups[m][j] = 1;
                        found = 1;
                        break;
                    }
                }
                if (!found)
                {
                    groups[g][i] = 1;
                    groups[g][j] = 1;
                    g++;
                }
                flags[i] = 1;
                flags[j] = 1;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                merge(n, groups, i, j);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (flags[i] == 0)
        {
            groups[g][i] = 1;
            g++;
        }
    }

    printf("\nMinimized DFA Transitions:\n");
    for (int i = 0; i < n; i++)
    {
        int j;
        for (j = 0; j < n && groups[i][j] == 0; j++)
            ;
        if (j == n)
            continue;

        printf("{");
        int first = 1;
        for (int k = 0; k < n; k++)
        {
            if (groups[i][k])
            {
                if (!first)
                    printf(",");
                printf("%c", states[k]);
                first = 0;
            }
        }
        printf("}");

        for (int b = 0; b < a; b++)
        {
            printf(" -%c-> ", alphabet[b]);
            int to_state = transition[j][b];

            for (int y = 0; y < n; y++)
            {
                if (groups[y][to_state])
                {
                    printf("{");
                    int first2 = 1;
                    for (int k = 0; k < n; k++)
                    {
                        if (groups[y][k])
                        {
                            if (!first2)
                                printf(",");
                            printf("%c", states[k]);
                            first2 = 0;
                        }
                    }
                    printf("}\n");
                    break;
                }
            }
        }
    }

    return 0;
}