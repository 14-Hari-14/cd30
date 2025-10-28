%{
#include "calc.tab.h"
%}


digit [0-9]+


%%
{digit}+          { yylval = atoi(yytext); return NUMBER; }
[ \t]           ;       // Ignore whitespace
\n              { return EOL; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MULT; }
"/"             { return DIV; }
"("             { return LPAREN; }
")"             { return RPAREN; }
.               { printf("Unknown character: %s\n", yytext); }
%%

int yywrap(void) {
    return 1;
}
