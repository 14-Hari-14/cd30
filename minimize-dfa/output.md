Enter number of states: 5
Enter state names (e.g., ABC): ABCDE
Enter size of alphabet: 2
Enter alphabet characters (e.g., ab): 01
Enter number of final states: 1
Enter final state names (e.g., B C): E
Enter number of transitions: 10
Enter transitions (format: A a B):
A 0 B
A 1 C
B 0 B
B 1 D
C 0 B
C 1 C
D 0 B
D 1 E
E 0 B
E 1 C

After marking initial distinguishable pairs:
0 0 0 0 0 
0 0 0 0 0 
0 0 0 0 0 
0 0 0 0 0 
1 1 1 1 0 

Final Myhill-Nerode Table:
0 0 0 0 0 
1 0 0 0 0 
0 1 0 0 0 
1 1 1 0 0 
1 1 1 1 0 

Minimized DFA Transitions:
{A,C} -0-> {B}
 -1-> {A,C}
{B} -0-> {B}
 -1-> {D}
{D} -0-> {B}
 -1-> {E}
{E} -0-> {B}
 -1-> {A,C}