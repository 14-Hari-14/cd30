%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
int yyerror(const char *msg);
%}

%union {
    int num;
}

%token <num> NUMBER
%token PLUS MINUS MULT DIV LPAREN RPAREN EOL

%left PLUS MINUS
%left MULT DIV
%type <num> expr

%%
calclist:
      | calclist expr EOL { printf("= %d\n", $2); }
      ;

expr:
      NUMBER              { $$ = $1; }
    | expr PLUS expr      { $$ = $1 + $3; }
    | expr MINUS expr     { $$ = $1 - $3; }
    | expr MULT expr      { $$ = $1 * $3; }
    | expr DIV expr       {
                            if ($3 == 0) {
                                yyerror("Division by zero");
                                exit(1);
                            }
                            $$ = $1 / $3;
                          }
    | LPAREN expr RPAREN  { $$ = $2; }
    ;
%%

int main() {
    printf("Enter expressions. Press Ctrl+D to exit.\n");
    yyparse();
    return 0;
}

int yyerror(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    return 0;
}
