#include <stdio.h>

#define MAX_STATES 20

// --- Global Variables ---
// This 2D array will ONLY store the e-moves.
int epsilon_moves[MAX_STATES][MAX_STATES] = {0};
int num_states;

/**
 * find_closure:
 * A simple DFS function to find all states reachable from 'state'
 * using only epsilon moves. This function is UNCHANGED.
 */
void find_closure(int state, int result_set[])
{
    // 1. Add the current state to the closure.
    result_set[state] = 1;

    // 2. Explore all neighbors via epsilon-moves.
    for (int i = 0; i < num_states; i++)
    {
        // IF (there is an e-move from 'state' to 'i')
        // AND (we haven't visited 'i' yet):
        if (epsilon_moves[state][i] == 1 && result_set[i] == 0)
        {
            // Recursively find the closure from that new state.
            find_closure(i, result_set);
        }
    }
}

int main()
{
    int total_num_trans, from, to;
    char symbol; // To read the transition symbol

    printf("Enter the number of states (e.g., 5): ");
    scanf("%d", &num_states);
    printf("NOTE: States must be numbered from 0 to %d.\n", num_states - 1);

    printf("Enter the TOTAL number of transitions (including all symbols): ");
    scanf("%d", &total_num_trans);

    printf("Enter all transitions (format: from symbol to):\n");
    printf("Example: 0 a 1\n");
    printf("         1 e 2\n");
    printf("         2 e 3\n");

    for (int i = 0; i < total_num_trans; i++)
    {
        // Read "from", "symbol", and "to"
        // The " %c" is important to skip whitespace before reading the char
        scanf("%d %c %d", &from, &symbol, &to);

        // *** THIS IS THE KEY LOGIC ***
        // Only if the symbol is 'e', we add it to our e-move graph.
        if (symbol == 'e')
        {
            epsilon_moves[from][to] = 1;
        }
        // All other transitions ('a', 'b', etc.) are read and ignored.
    }

    printf("\n----------------------\n");
    printf("E-Closures:\n");
    printf("----------------------\n");

    // This loop is UNCHANGED.
    for (int i = 0; i < num_states; i++)
    {
        int result_set[MAX_STATES] = {0};

        find_closure(i, result_set);

        // Print the final set
        printf("e-closure(%d) = { ", i);
        for (int j = 0; j < num_states; j++)
        {
            if (result_set[j] == 1)
            {
                printf("%d ", j);
            }
        }
        printf("}\n");
    }

    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>

// struct node
// {
//     int st;
//     struct node *link;
// };

// void findclosure(int x, int sta);
// void insert_trantbl(int r, char c, int s);
// int findalpha(char c);
// void print_e_closure(int i);

// static int set[20], nostate, noalpha, s, notransition;
// static int buffer[20];
// static int e_closure[20][20];
// char alphabet[20];
// struct node *transition[20][20] = {NULL};
// int c;

// int main()
// {
//     int i, j, from, to;
//     char symbol;

//     for (i = 0; i < 20; i++)
//         for (j = 0; j < 20; j++)
//             e_closure[i][j] = -1;

//     printf("Enter the number of alphabets: ");
//     scanf("%d", &noalpha);

//     printf("NOTE:- [Use letter 'e' as epsilon]\n");
//     printf("NOTE:- [e must be the last character if it is present]\n");

//     printf("\nEnter alphabets:\n");
//     for (i = 0; i < noalpha; i++)
//     {
//         scanf(" %c", &alphabet[i]);
//     }

//     printf("\nEnter the number of states: ");
//     scanf("%d", &nostate);

//     printf("Enter number of transitions: ");
//     scanf("%d", &notransition);

//     printf("NOTE:- [Transition format: state1 alphabet state2]\n");
//     printf("NOTE:- [State numbers must be >= 1]\n");
//     printf("\nEnter transitions:\n");

//     for (i = 0; i < notransition; i++)
//     {
//         scanf("%d %c %d", &from, &symbol, &to);
//         insert_trantbl(from, symbol, to);
//     }

//     printf("\nE-closures of states:\n");
//     printf("----------------------\n");

//     for (i = 1; i <= nostate; i++)
//     {
//         c = 0;
//         for (j = 0; j < 20; j++)
//             buffer[j] = 0;
//         findclosure(i, i);
//         printf("e-closure(q%d): ", i);
//         print_e_closure(i);
//         printf("\n");
//     }

//     return 0;
// }

// void findclosure(int x, int sta)
// {
//     if (buffer[x])
//         return;

//     e_closure[sta][c++] = x;
//     buffer[x] = 1;

//     if (alphabet[noalpha - 1] == 'e' && transition[x][noalpha - 1] != NULL)
//     {
//         struct node *temp = transition[x][noalpha - 1];
//         while (temp != NULL)
//         {
//             findclosure(temp->st, sta);
//             temp = temp->link;
//         }
//     }
// }

// void insert_trantbl(int r, char c, int s)
// {
//     int j = findalpha(c);
//     if (j == 999)
//     {
//         printf("Invalid alphabet: %c\n", c);
//         exit(1);
//     }

//     struct node *temp = (struct node *)malloc(sizeof(struct node));
//     temp->st = s;
//     temp->link = transition[r][j];
//     transition[r][j] = temp;
// }

// int findalpha(char c)
// {
//     for (int i = 0; i < noalpha; i++)
//     {
//         if (alphabet[i] == c)
//             return i;
//     }
//     return 999;
// }

// void print_e_closure(int i)
// {
//     printf("{");
//     for (int j = 0; e_closure[i][j] != -1; j++)
//     {
//         printf("q%d", e_closure[i][j]);
//         if (e_closure[i][j + 1] != -1)
//             printf(", ");
//     }
//     printf("}");
// }