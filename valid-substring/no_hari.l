%{
    #include <stdio.h>
%}

%%
exit { printf("Exiting the program.\n"); exit(0); }
.*[Hh][Aa][Rr][Ii].* { printf("Rejected: %s\n", yytext); }
.* { printf("Accepted: %s\n", yytext); }
%%

int yywrap(void) {
    return 1;
}

int main() {
    yylex();
}