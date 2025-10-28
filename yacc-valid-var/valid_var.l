%{
#include "valid_var.tab.h"
%}

%%
[a-zA-Z][a-zA-Z0-9]*[ \t]*\n     { return IDENTIFIER; }
[^\n]*\n                         { return INVALID; }
%%

int yywrap() {
    return 1;
}
