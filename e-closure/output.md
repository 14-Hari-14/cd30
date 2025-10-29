Enter the number of alphabets: 2
NOTE:- [Use letter 'e' as epsilon]
NOTE:- [e must be the last character if it is present]

Enter alphabets:
0
e

Enter the number of states: 3
Enter number of transitions: 3
NOTE:- [Transition format: state1 alphabet state2]
NOTE:- [State numbers must be >= 1]

Enter transitions:
1 e 2
2 e 3
2 0 1

## E-closures of states:

e-closure(q1): {q1, q2, q3}
e-closure(q2): {q2, q3}
e-closure(q3): {q3}

algo

Initialization 
1.1. Create a 2D array epsilon_moves[MAX][MAX] and initialize all to 0. This will only store ϵ-transitions. 
1.2. Create a 1D array result_set[MAX] (as a temporary buffer). 
1.3. Ask user for num_states (number of states). 1.4. Ask user for total_num_transitions (for 'a', 'b', 'e', etc.).

Input & Graph Building 
2.1. Loop total_num_transitions times: 
    2.1.1. Read from_state, symbol, to_state. 
    2.1.2. Filter: IF symbol == 'e': _ Set epsilon_moves[from_state][to_state] = 1. _ (Else, do nothing. We are "ignoring" all 'a', 'b', etc. transitions).

Main Loop (Finding Closure for Each State) 
3.1. FOR each state i from 0 to num_states - 1: 
    3.1.1. Reset result_set to all 0s (false). 
    3.1.2. Call the recursive function find_closure(i, result_set). 
    3.1.3. Print the result: _ Print "e-closure(i) = { ". _ Loop from j = 0 to num_states - 1: _ If result_set[j] == 1, print j. _ Print " }".

Recursive Function: find_closure(int state, int result_set[]) 
4.1. Add self: Add the current state to the closure set. This also marks it as "visited." _ result_set[state] = 1. 
4.2. Explore neighbors: _ FOR each state i from 0 to num_states - 1: _ IF (there is an ϵ-move from state to i) AND (i is not in the result_set yet): _ Recursively call find_closure(i, result_set).
