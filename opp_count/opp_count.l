%{
    #include<stdio.h>
    int counter = 0;
%}

%%
"++"|"--"|"+"|"-"|"*"|"/"|"^"|"%" { counter++; }

"exit" { printf("done\n"); return 0; }

[ \t\n]+     { /* skip whitespace */ }

. { /* ignore other characters */ }

%%
int main(){
    yylex();
    printf("Total no of operators are: %d\n", counter);
}

int yywrap(){
    return 1;
}