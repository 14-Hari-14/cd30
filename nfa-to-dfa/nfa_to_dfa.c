#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

char tran[MAX][MAX][MAX];

int eclosure[MAX][MAX];
int closurecount[MAX];

int dfastate[MAX][MAX];
int dfastatecount[MAX];

char input[MAX];
int n_alpha, n_state, n_trans, start, n_final;
int final[MAX];

int dfa[MAX][MAX];
int dfa_state_total = 0;

int is_final_state(int state)
{
    for (int i = 0; i < n_final; i++)
    {
        if (final[i] == state)
            return 1;
    }
    return 0;
}

int find_alpha_index(char ch)
{
    for (int i = 0; i < n_alpha; i++)
    {
        if (input[i] == ch)
            return i;
    }
    return -1;
}

void add_transition(int from, int to, char symbol)
{
    if (strchr(tran[from][to], symbol) == NULL)
    {
        int len = strlen(tran[from][to]);
        tran[from][to][len] = symbol;
        tran[from][to][len + 1] = '\0';
    }
}

void compute_eclosure()
{
    for (int i = 0; i < n_state; i++)
    {
        int visited[MAX] = {0}, stack[MAX], top = -1;
        eclosure[i][0] = i;
        closurecount[i] = 1;
        visited[i] = 1;
        stack[++top] = i;

        while (top >= 0)
        {
            int curr = stack[top--];
            for (int j = 0; j < n_state; j++)
            {
                if (strchr(tran[curr][j], 'e') && !visited[j])
                {
                    eclosure[i][closurecount[i]++] = j;
                    visited[j] = 1;
                    stack[++top] = j;
                }
            }
        }
    }
}

int get_dfa_state_index(int state_list[], int count)
{
    for (int i = 0; i < dfa_state_total; i++)
    {
        if (dfastatecount[i] != count)
            continue;
        int match = 1;
        for (int j = 0; j < count; j++)
        {
            if (dfastate[i][j] != state_list[j])
            {
                match = 0;
                break;
            }
        }
        if (match)
            return i;
    }
    return -1;
}

void sort_state_list(int list[], int count)
{
    for (int i = 0; i < count - 1; i++)
        for (int j = i + 1; j < count; j++)
            if (list[i] > list[j])
            {
                int t = list[i];
                list[i] = list[j];
                list[j] = t;
            }
}

void subset_construction()
{
    int queue[MAX][MAX], front = 0, rear = 0;
    int initial[MAX], init_count = 0;
    int queuecount[MAX] = {0};

    for (int i = 0; i < closurecount[start]; i++)
        initial[i] = eclosure[start][i];
    init_count = closurecount[start];
    sort_state_list(initial, init_count);

    int unique_init[MAX], unique_init_count = 0;
    for (int i = 0; i < init_count; i++)
    {
        if (i == 0 || initial[i] != initial[i - 1])
            unique_init[unique_init_count++] = initial[i];
    }

    memcpy(dfastate[0], unique_init, sizeof(int) * unique_init_count);
    dfastatecount[0] = unique_init_count;
    dfa_state_total = 1;

    memcpy(queue[rear], unique_init, sizeof(int) * unique_init_count);
    queuecount[rear] = unique_init_count;
    rear++;

    while (front < rear)
    {
        int *curr = queue[front];
        int currcount = queuecount[front];
        int curr_index = get_dfa_state_index(curr, currcount);
        front++;

        for (int a = 0; a < n_alpha; a++)
        {
            int move[MAX], move_count = 0;
            for (int i = 0; i < currcount; i++)
            {
                int state = curr[i];
                for (int j = 0; j < n_state; j++)
                {
                    if (strchr(tran[state][j], input[a]))
                    {
                        for (int k = 0; k < closurecount[j]; k++)
                        {
                            int s = eclosure[j][k];
                            int exists = 0;
                            for (int m = 0; m < move_count; m++)
                            {
                                if (move[m] == s)
                                {
                                    exists = 1;
                                    break;
                                }
                            }
                            if (!exists)
                                move[move_count++] = s;
                        }
                    }
                }
            }

            sort_state_list(move, move_count);
            int unique_move[MAX], unique_move_count = 0;
            for (int i = 0; i < move_count; i++)
            {
                if (i == 0 || move[i] != move[i - 1])
                    unique_move[unique_move_count++] = move[i];
            }

            int idx = get_dfa_state_index(unique_move, unique_move_count);
            if (idx == -1 && unique_move_count > 0)
            {
                memcpy(dfastate[dfa_state_total], unique_move, sizeof(int) * unique_move_count);
                dfastatecount[dfa_state_total] = unique_move_count;
                memcpy(queue[rear], unique_move, sizeof(int) * unique_move_count);
                queuecount[rear] = unique_move_count;
                idx = dfa_state_total;
                dfa_state_total++;
                rear++;
            }

            dfa[curr_index][a] = idx;
        }
    }
}

void print_dfa()
{
    printf("\nDFA Transition Table:\n");
    printf("---------------------\n\t");
    for (int i = 0; i < n_alpha; i++)
        printf("%c\t", input[i]);
    printf("\n");

    for (int i = 0; i < dfa_state_total; i++)
    {

        int is_final = 0;
        for (int j = 0; j < dfastatecount[i]; j++)
        {
            if (is_final_state(dfastate[i][j]))
            {
                is_final = 1;
                break;
            }
        }
        if (is_final)
            printf("*");
        else
            printf(" ");
        printf("{");
        for (int j = 0; j < dfastatecount[i]; j++)
        {
            printf("q%d", dfastate[i][j]);
            if (j != dfastatecount[i] - 1)
                printf(" ");
        }
        printf("}\t");
        for (int k = 0; k < n_alpha; k++)
        {
            int to = dfa[i][k];
            if (to == -1)
                printf("-\t");
            else
            {
                printf("{");
                for (int j = 0; j < dfastatecount[to]; j++)
                {
                    printf("q%d", dfastate[to][j]);
                    if (j != dfastatecount[to] - 1)
                        printf(" ");
                }
                printf("}\t");
            }
        }
        printf("\n");
    }
}

int main()
{
    memset(tran, 0, sizeof(tran));
    memset(dfa, -1, sizeof(dfa));

    printf("Enter number of alphabets: ");
    scanf("%d", &n_alpha);
    getchar();
    printf("Enter the alphabets (e for epsilon, should be last):\n");
    for (int i = 0; i < n_alpha; i++)
    {
        scanf("%c", &input[i]);
        getchar();
    }

    printf("Enter number of states: ");
    scanf("%d", &n_state);
    printf("Enter number of transitions: ");
    scanf("%d", &n_trans);
    printf("Enter transitions (from symbol to):\n");
    for (int i = 0; i < n_trans; i++)
    {
        int from, to;
        char ch;
        scanf("%d %c %d", &from, &ch, &to);
        add_transition(from, to, ch);
    }

    printf("Enter the start state: ");
    scanf("%d", &start);
    printf("Enter number of final states: ");
    scanf("%d", &n_final);
    printf("Enter final states: ");
    for (int i = 0; i < n_final; i++)
        scanf("%d", &final[i]);

    compute_eclosure();
    subset_construction();
    print_dfa();

    return 0;
}