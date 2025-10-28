%{
    #include "y.tab.h"
%}

%%
"for" {return FOR;}
"exit" {printf("done\n"); exit(0);}

"++"|"--" {return INC;}

[0-9]+ {yylval = atoi(yytext); return NUMBER;}
[a-zA-Z]+ {return ID;}

[ \t\n] { /* ignore whitespace */ }
. {return yytext[0];}
%%

int yywrap(){
    return 1;
}
