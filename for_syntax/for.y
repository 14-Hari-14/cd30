%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>

    // Function prototypes
    int yylex(void);
    int yyerror(const char *s);
%}

%token FOR ID NUMBER INC 
/* %start optional */

%%
input: 
    | input stmt
;
stmt: FOR '(' init_opt ';' cond_opt ';' inc_opt ')'  { printf("Valid FOR statement syntax\n"); };

init_opt: 
ID ID '=' ID
|ID '=' ID
|ID '=' NUMBER
|ID ID '=' NUMBER
;

cond_opt:
ID '<' ID
| ID '<' NUMBER
| ID '>' ID
| ID '>' NUMBER
;

inc_opt:
ID INC
;
%%

int main(){
    printf("Enter the FOR statement:\n");
    yyparse(); //yylex already in yyparse
    return 0;
}

int yyerror(const char *s){
    printf("Error: %s\n", s);
    return 0;
}

