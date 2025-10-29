#include <stdio.h>
#include <string.h>

#define MAX_STATES 20
#define MAX_ALPHABETS 5
#define MAX_NEW_STATES 20

// --- Globals for e-NFA ---
int num_states;
int start_state;
char alphabet[MAX_ALPHABETS];
int num_alphabets;

// e_moves[i][j] = 1 means e-move from i to j
int epsilon_moves[MAX_STATES][MAX_STATES] = {0};
// move_transitions[from][alpha_index][to] = 1
int move_transitions[MAX_STATES][MAX_ALPHABETS][MAX_STATES] = {0};

// --- Globals for new NFA ---
// new_states[0] = {1, 1, 0, 0} means S0 = {0, 1}
int new_states[MAX_NEW_STATES][MAX_STATES] = {0};
int new_nfa_transitions[MAX_NEW_STATES][MAX_ALPHABETS] = {0};
int new_states_count = 0;

// --- Helper Functions ---

/**
 * find_closure_recursive (Your e-closure function)
 * A simple DFS to add all e-reachable states from 'state' to 'result_set'.
 */
void find_closure_recursive(int state, int result_set[])
{
    result_set[state] = 1;
    for (int i = 0; i < num_states; i++)
    {
        if (epsilon_moves[state][i] == 1 && result_set[i] == 0)
        {
            find_closure_recursive(i, result_set);
        }
    }
}

/**
 * e_closure_set
 * Calculates the e-closure for an entire SET of states.
 */
void e_closure_set(int input_set[], int result_set[])
{
    // 1. Clear the result set
    for (int i = 0; i < num_states; i++)
        result_set[i] = 0;

    // 2. For every state in the input set, add its e-closure
    for (int i = 0; i < num_states; i++)
    {
        if (input_set[i] == 1)
        {
            find_closure_recursive(i, result_set);
        }
    }
}

/**
 * move
 * Calculates where a SET of states moves on a given symbol.
 */
void move(int input_set[], int alpha_index, int result_set[])
{
    // 1. Clear the result set
    for (int i = 0; i < num_states; i++)
        result_set[i] = 0;

    // 2. For every state in the input set
    for (int i = 0; i < num_states; i++)
    {
        if (input_set[i] == 1)
        {
            // Check all possible 'to' states
            for (int j = 0; j < num_states; j++)
            {
                if (move_transitions[i][alpha_index][j] == 1)
                {
                    result_set[j] = 1;
                }
            }
        }
    }
}

// Finds the index of a given alphabet symbol
int find_alpha_index(char symbol)
{
    for (int i = 0; i < num_alphabets; i++)
    {
        if (alphabet[i] == symbol)
            return i;
    }
    return -1; // Not found
}

// Checks if two sets (arrays) are identical
int is_same_set(int set1[], int set2[])
{
    for (int i = 0; i < num_states; i++)
    {
        if (set1[i] != set2[i])
            return 0; // Not same
    }
    return 1; // Same
}

// Checks if a set is empty (all zeros)
int is_set_empty(int set[])
{
    for (int i = 0; i < num_states; i++)
    {
        if (set[i] == 1)
            return 0; // Not empty
    }
    return 1; // Empty
}

// Checks if a state (set) already exists in our new_states table
// Returns its index if found, -1 if not
int find_existing_state(int set[])
{
    for (int i = 0; i < new_states_count; i++)
    {
        if (is_same_set(new_states[i], set))
        {
            return i;
        }
    }
    return -1;
}

// Helper to print a state set
void print_set(int set[])
{
    printf("{ ");
    for (int i = 0; i < num_states; i++)
    {
        if (set[i] == 1)
            printf("%d ", i);
    }
    printf("}");
}

// --- Main Function ---
int main()
{
    int total_trans, from, to;
    char symbol;

    // --- 1. Get e-NFA Input ---
    printf("Enter number of states in e-NFA: ");
    scanf("%d", &num_states);
    printf("Enter the start state: ");
    scanf("%d", &start_state);

    printf("Enter number of alphabets (excluding 'e'): ");
    scanf("%d", &num_alphabets);
    printf("Enter the alphabets: ");
    for (int i = 0; i < num_alphabets; i++)
    {
        scanf(" %c", &alphabet[i]);
    }

    printf("Enter total number of transitions: ");
    scanf("%d", &total_trans);
    printf("Enter transitions (from symbol to):\n");
    for (int i = 0; i < total_trans; i++)
    {
        scanf("%d %c %d", &from, &symbol, &to);
        if (symbol == 'e')
        {
            epsilon_moves[from][to] = 1;
        }
        else
        {
            int alpha_index = find_alpha_index(symbol);
            if (alpha_index != -1)
            {
                move_transitions[from][alpha_index][to] = 1;
            }
        }
    }

    // --- 2. Start Conversion ---
    int work_queue[MAX_NEW_STATES];
    int queue_head = 0, queue_tail = 0;

    // 2.1 Create S0 (Start State of new NFA)
    int temp_set[MAX_STATES] = {0};
    temp_set[start_state] = 1;
    e_closure_set(temp_set, new_states[0]); // S0 = e_closure(start_state)
    new_states_count = 1;
    work_queue[queue_tail++] = 0; // Add S0 to the work queue

    // 2.2 Main Conversion Loop
    while (queue_head < queue_tail)
    {
        int current_state_index = work_queue[queue_head++]; // Dequeue

        for (int i = 0; i < num_alphabets; i++)
        {
            int move_set[MAX_STATES];
            int closure_set[MAX_STATES];

            // 1. move(S_current, symbol)
            move(new_states[current_state_index], i, move_set);

            // 2. e_closure(move_set)
            e_closure_set(move_set, closure_set);

            if (is_set_empty(closure_set))
            {
                new_nfa_transitions[current_state_index][i] = -1; // -1 = dead state
                continue;
            }

            // 3. Check if this new set already exists
            int existing_index = find_existing_state(closure_set);

            if (existing_index != -1)
            {
                // It exists, just add the transition
                new_nfa_transitions[current_state_index][i] = existing_index;
            }
            else
            {
                // It's a new state!
                // Add it to our list of states
                memcpy(new_states[new_states_count], closure_set, sizeof(int) * MAX_STATES);
                // Add the transition
                new_nfa_transitions[current_state_index][i] = new_states_count;
                // Add new state to work queue
                work_queue[queue_tail++] = new_states_count;
                // Increment count
                new_states_count++;
            }
        }
    }

    // --- 3. Print Results ---
    printf("\n--- NFA Conversion Complete ---\n");
    printf("\nNew States:\n");
    for (int i = 0; i < new_states_count; i++)
    {
        printf("S%d = ", i);
        print_set(new_states[i]);
        printf("\n");
    }

    printf("\nNew NFA Transition Table:\n");
    for (int i = 0; i < new_states_count; i++)
    {
        for (int j = 0; j < num_alphabets; j++)
        {
            if (new_nfa_transitions[i][j] != -1)
            {
                printf("S%d --%c--> S%d\n", i, alphabet[j], new_nfa_transitions[i][j]);
            }
        }
    }

    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define MAX_STATES 100
// #define MAX_ALPHABET 10

// struct node
// {
//     int st;
//     struct node *link;
// };

// void findclosure(int original_state, int current_state);
// void insert_trantbl(int r, char c, int s);
// int findalpha(char c);

// struct node *transition[MAX_STATES][MAX_ALPHABET] = {NULL};
// int e_closure[MAX_STATES][MAX_STATES];
// char alphabet[MAX_ALPHABET];
// int nostate, noalpha, start_state, nofinal;
// int final_states[MAX_STATES];
// int closure_buffer[MAX_STATES];
// int closure_count;

// int main()
// {
//     int i, j, k, from, to;

//     printf("Enter the number of alphabets: ");
//     scanf("%d", &noalpha);

//     printf("NOTE: [Use 'e' for epsilon, and make sure it's the LAST character if present]\n");
//     printf("Enter the alphabets:\n");
//     for (i = 0; i < noalpha; i++)
//     {
//         scanf(" %c", &alphabet[i]);
//     }

//     printf("Enter the number of states (e.g., 3 for states 0, 1, 2): ");
//     scanf("%d", &nostate);

//     printf("Enter the start state: ");
//     scanf("%d", &start_state);

//     printf("Enter the number of final states: ");
//     scanf("%d", &nofinal);

//     printf("Enter the final states:\n");
//     for (i = 0; i < nofinal; i++)
//     {
//         scanf("%d", &final_states[i]);
//     }

//     printf("Enter number of transitions: ");
//     int notransition;
//     scanf("%d", &notransition);

//     printf("NOTE: [Enter transitions in the form: <from_state> <symbol> <to_state>]\n");
//     for (i = 0; i < notransition; i++)
//     {
//         char c_char;
//         scanf("%d %c %d", &from, &c_char, &to);
//         insert_trantbl(from, c_char, to);
//     }

//     printf("\n--- Epsilon Closures ---\n");
//     for (i = 0; i < nostate; i++)
//     {
//         closure_count = 0;
//         for (k = 0; k < MAX_STATES; k++)
//         {
//             closure_buffer[k] = 0;
//             e_closure[i][k] = -1;
//         }

//         findclosure(i, i);

//         printf("E(%d) = { ", i);
//         for (j = 0; j < MAX_STATES && e_closure[i][j] != -1; j++)
//         {
//             printf("%d ", e_closure[i][j]);
//         }
//         printf("}\n");
//     }

//     printf("\nEquivalent NFA without Epsilon Transitions:\n");
//     printf("===========================================\n");

//     printf("Start State: q%d\n", start_state);

//     printf("Alphabets: ");
//     for (i = 0; i < noalpha; i++)
//     {
//         if (alphabet[i] != 'e')
//         {
//             printf("%c ", alphabet[i]);
//         }
//     }
//     printf("\n");

//     printf("States: ");
//     for (i = 0; i < nostate; i++)
//     {
//         printf("q%d ", i);
//     }
//     printf("\n");

//     printf("Transitions:\n");
//     for (i = 0; i < nostate; i++)
//     {
//         for (j = 0; j < noalpha; j++)
//         {
//             if (alphabet[j] == 'e')
//                 continue;

//             int result_set[MAX_STATES] = {0};

//             for (k = 0; k < MAX_STATES && e_closure[i][k] != -1; k++)
//             {
//                 int state_in_closure = e_closure[i][k];
//                 struct node *temp = transition[state_in_closure][j];
//                 while (temp != NULL)
//                 {
//                     for (int l = 0; l < MAX_STATES && e_closure[temp->st][l] != -1; l++)
//                     {
//                         result_set[e_closure[temp->st][l]] = 1;
//                     }
//                     temp = temp->link;
//                 }
//             }

//             printf("q%d -- %c --> { ", i, alphabet[j]);
//             int first = 1;
//             for (k = 0; k < nostate; k++)
//             {
//                 if (result_set[k])
//                 {
//                     if (!first)
//                         printf(", ");
//                     printf("q%d", k);
//                     first = 0;
//                 }
//             }
//             if (first)
//                 printf("(none)");
//             printf(" }\n");
//         }
//     }

//     printf("\nFinal States: { ");
//     int is_new_final[MAX_STATES] = {0};
//     for (i = 0; i < nostate; i++)
//     {
//         for (j = 0; j < MAX_STATES && e_closure[i][j] != -1; j++)
//         {
//             for (k = 0; k < nofinal; k++)
//             {
//                 if (e_closure[i][j] == final_states[k])
//                 {
//                     is_new_final[i] = 1;
//                     break;
//                 }
//             }
//             if (is_new_final[i])
//                 break;
//         }
//     }

//     int first = 1;
//     for (i = 0; i < nostate; i++)
//     {
//         if (is_new_final[i])
//         {
//             if (!first)
//                 printf(", ");
//             printf("q%d", i);
//             first = 0;
//         }
//     }
//     printf(" }\n");

//     return 0;
// }

// void findclosure(int original_state, int current_state)
// {
//     if (closure_buffer[current_state])
//         return;

//     if (closure_count >= MAX_STATES)
//     {
//         printf("Error: Closure too large for state %d\n", original_state);
//         exit(1);
//     }

//     e_closure[original_state][closure_count++] = current_state;
//     closure_buffer[current_state] = 1;

//     int e_alpha_index = findalpha('e');
//     if (e_alpha_index == 999)
//         return;

//     struct node *temp = transition[current_state][e_alpha_index];
//     while (temp != NULL)
//     {
//         findclosure(original_state, temp->st);
//         temp = temp->link;
//     }
// }

// void insert_trantbl(int r, char c, int s)
// {
//     int j = findalpha(c);
//     if (j == 999)
//     {
//         printf("Symbol %c not in alphabet\n", c);
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