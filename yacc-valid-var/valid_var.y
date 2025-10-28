%{
#include <stdio.h>
#include <stdlib.h>

// DECLARATIONS TO FIX WARNINGS
int yylex();             // From lex
int yyerror(const char*); // Your error handler
%}

%token IDENTIFIER INVALID

%%
input:
      IDENTIFIER          { printf("Valid variable\n"); }
    | INVALID             { printf("Invalid variable\n"); }
    ;
%%

int yyerror(const char *s) {
    printf("Invalid variable name\n");
    return 1;
}

int main() {
    printf("Enter a variable name: ");
    yyparse();
    return 0;
}
