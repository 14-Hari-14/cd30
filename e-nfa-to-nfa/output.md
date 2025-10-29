code1
Enter number of states in e-NFA: 3
Enter the start state: 0
Enter number of alphabets (excluding 'e'): 2
Enter the alphabets: 0 1
Enter total number of transitions: 5
Enter transitions (from symbol to):
0 0 0
0 e 1
1 1 1
1 e 2
2 0 2

--- NFA Conversion Complete ---

New States:
S0 = { 0 1 2 }
S1 = { 1 2 }
S2 = { 2 }

New NFA Transition Table:
S0 --0--> S0
S0 --1--> S1
S1 --0--> S2
S1 --1--> S1
S2 --0--> S2

code 2
Enter the number of alphabets: 3
NOTE: [Use 'e' for epsilon, and make sure it's the LAST character if present]
Enter the alphabets:
0
1
e
Enter the number of states (e.g., 3 for states 0, 1, 2): 3
Enter the start state: 0
Enter the number of final states: 1
Enter the final states:
2
Enter number of transitions: 5
NOTE: [Enter transitions in the form: <from_state> <symbol> <to_state>]
0 0 0
0 e 1
1 1 1
1 e 2
2 0 2

--- Epsilon Closures ---
E(0) = { 0 1 2 }
E(1) = { 1 2 }
E(2) = { 2 }

# Equivalent NFA without Epsilon Transitions:

Start State: q0
Alphabets: 0 1
States: q0 q1 q2
Transitions:
q0 -- 0 --> { q0, q1, q2 }
q0 -- 1 --> { q1, q2 }
q1 -- 0 --> { q2 }
q1 -- 1 --> { q1, q2 }
q2 -- 0 --> { q2 }
q2 -- 1 --> { (none) }

Final States: { q0, q1, q2 }
