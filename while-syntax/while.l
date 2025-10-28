%{
    #include "y.tab.h"
%}

%%

"while" {return WHILE;}
"exit" {printf("done\n"); exit(0);}
"<="|">="|"=="|"<"|">" {return RELOP;}

[0-9]+ {yylval = atoi(yytext); return NUMBER;}
[a-zA-Z]+ {return ID;}

"{"[^}]*"}" {return CODE;}
[ \t\n] {/*ignore whitespace */}
. {return yytext[0];}

%%

int yywrap(){
    return 1;
}