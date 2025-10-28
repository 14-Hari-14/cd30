%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    
    int yylex(void);
    int yyerror(const char *s);
%}

%token IF RELOP ID NUMBER ELSE CODE

%%
input: 
    | input stmt
;

stmt: IF '(' condition ')' CODE ELSE CODE { printf("Valid expression\n"); } ;

condition:
        ID RELOP NUMBER
    | ID RELOP ID
    ;

%%

int main(){
    printf("Enter the IF statement: \n");
    yyparse();
    return 0;
}

int yyerror(const char *s){
    printf("Error: %s\n", s);
    return 0;
}