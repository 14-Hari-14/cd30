%{
    #include<stdio.h>
    
    int yylex(void);
    int yyerror(const char *s);
%}

%token WHILE RELOP CODE ID NUMBER

%%

input: 
    | input stmt

;

stmt: WHILE '('cond')' CODE {printf("Valid while loop");};

cond: ID RELOP NUMBER
    | ID RELOP ID
    | NUMBER RELOP NUMBER
    | NUMBER RELOP ID
    ;

%%

int main(){
    printf("Enter the while statement: \n");
    yyparse();
    return 0;
}

int yyerror(const char *s){
    printf("Error: %s\n", s);
    return 0;
}