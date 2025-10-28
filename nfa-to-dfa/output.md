Enter number of alphabets: 2
Enter the alphabets (e for epsilon, should be last):
a
b
Enter number of states: 3
Enter number of transitions: 5
Enter transitions (from symbol to):
0 a 2
0 a 1
2 a 2
2 b 2
2 a 1
Enter the start state: 0
Enter number of final states: 1
Enter final states: 1

DFA Transition Table:
---------------------
        a       b
 {q0}   {q1 q2} -
*{q1 q2}        {q1 q2} {q2}
 {q2}   {q1 q2} {q2}