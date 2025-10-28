#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_ALPHABET 10

struct node
{
    int st;
    struct node *link;
};

void findclosure(int original_state, int current_state);
void insert_trantbl(int r, char c, int s);
int findalpha(char c);

struct node *transition[MAX_STATES][MAX_ALPHABET] = {NULL};
int e_closure[MAX_STATES][MAX_STATES];
char alphabet[MAX_ALPHABET];
int nostate, noalpha, start_state, nofinal;
int final_states[MAX_STATES];
int closure_buffer[MAX_STATES];
int closure_count;

int main()
{
    int i, j, k, from, to;

    printf("Enter the number of alphabets: ");
    scanf("%d", &noalpha);

    printf("NOTE: [Use 'e' for epsilon, and make sure it's the LAST character if present]\n");
    printf("Enter the alphabets:\n");
    for (i = 0; i < noalpha; i++)
    {
        scanf(" %c", &alphabet[i]);
    }

    printf("Enter the number of states (e.g., 3 for states 0, 1, 2): ");
    scanf("%d", &nostate);

    printf("Enter the start state: ");
    scanf("%d", &start_state);

    printf("Enter the number of final states: ");
    scanf("%d", &nofinal);

    printf("Enter the final states:\n");
    for (i = 0; i < nofinal; i++)
    {
        scanf("%d", &final_states[i]);
    }

    printf("Enter number of transitions: ");
    int notransition;
    scanf("%d", &notransition);

    printf("NOTE: [Enter transitions in the form: <from_state> <symbol> <to_state>]\n");
    for (i = 0; i < notransition; i++)
    {
        char c_char;
        scanf("%d %c %d", &from, &c_char, &to);
        insert_trantbl(from, c_char, to);
    }

    printf("\n--- Epsilon Closures ---\n");
    for (i = 0; i < nostate; i++)
    {
        closure_count = 0;
        for (k = 0; k < MAX_STATES; k++)
        {
            closure_buffer[k] = 0;
            e_closure[i][k] = -1;
        }

        findclosure(i, i);

        printf("E(%d) = { ", i);
        for (j = 0; j < MAX_STATES && e_closure[i][j] != -1; j++)
        {
            printf("%d ", e_closure[i][j]);
        }
        printf("}\n");
    }

    printf("\nEquivalent NFA without Epsilon Transitions:\n");
    printf("===========================================\n");

    printf("Start State: q%d\n", start_state);

    printf("Alphabets: ");
    for (i = 0; i < noalpha; i++)
    {
        if (alphabet[i] != 'e')
        {
            printf("%c ", alphabet[i]);
        }
    }
    printf("\n");

    printf("States: ");
    for (i = 0; i < nostate; i++)
    {
        printf("q%d ", i);
    }
    printf("\n");

    printf("Transitions:\n");
    for (i = 0; i < nostate; i++)
    {
        for (j = 0; j < noalpha; j++)
        {
            if (alphabet[j] == 'e')
                continue;

            int result_set[MAX_STATES] = {0};

            for (k = 0; k < MAX_STATES && e_closure[i][k] != -1; k++)
            {
                int state_in_closure = e_closure[i][k];
                struct node *temp = transition[state_in_closure][j];
                while (temp != NULL)
                {
                    for (int l = 0; l < MAX_STATES && e_closure[temp->st][l] != -1; l++)
                    {
                        result_set[e_closure[temp->st][l]] = 1;
                    }
                    temp = temp->link;
                }
            }

            printf("q%d -- %c --> { ", i, alphabet[j]);
            int first = 1;
            for (k = 0; k < nostate; k++)
            {
                if (result_set[k])
                {
                    if (!first)
                        printf(", ");
                    printf("q%d", k);
                    first = 0;
                }
            }
            if (first)
                printf("(none)");
            printf(" }\n");
        }
    }

    printf("\nFinal States: { ");
    int is_new_final[MAX_STATES] = {0};
    for (i = 0; i < nostate; i++)
    {
        for (j = 0; j < MAX_STATES && e_closure[i][j] != -1; j++)
        {
            for (k = 0; k < nofinal; k++)
            {
                if (e_closure[i][j] == final_states[k])
                {
                    is_new_final[i] = 1;
                    break;
                }
            }
            if (is_new_final[i])
                break;
        }
    }

    int first = 1;
    for (i = 0; i < nostate; i++)
    {
        if (is_new_final[i])
        {
            if (!first)
                printf(", ");
            printf("q%d", i);
            first = 0;
        }
    }
    printf(" }\n");

    return 0;
}

void findclosure(int original_state, int current_state)
{
    if (closure_buffer[current_state])
        return;

    if (closure_count >= MAX_STATES)
    {
        printf("Error: Closure too large for state %d\n", original_state);
        exit(1);
    }

    e_closure[original_state][closure_count++] = current_state;
    closure_buffer[current_state] = 1;

    int e_alpha_index = findalpha('e');
    if (e_alpha_index == 999)
        return;

    struct node *temp = transition[current_state][e_alpha_index];
    while (temp != NULL)
    {
        findclosure(original_state, temp->st);
        temp = temp->link;
    }
}

void insert_trantbl(int r, char c, int s)
{
    int j = findalpha(c);
    if (j == 999)
    {
        printf("Symbol %c not in alphabet\n", c);
        exit(1);
    }
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->st = s;
    temp->link = transition[r][j];
    transition[r][j] = temp;
}

int findalpha(char c)
{
    for (int i = 0; i < noalpha; i++)
    {
        if (alphabet[i] == c)
            return i;
    }
    return 999;
}