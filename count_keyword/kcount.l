%{
    #include<stdio.h>
    #include<string.h>
    int counter = 0;
// "if"|"else"|"else if"|"while"|"for"|"int"|"char"|"float"|"printf" {counter++;}
%}

ID [a-zA-Z_][a-zA-Z0-9_]*

%%
"exit" {printf("done\n"); return 0;}

{ID} {
    if(strcmp(yytext, "if") == 0 ||
       strcmp(yytext, "else") == 0 ||
       strcmp(yytext, "else if") == 0 ||
       strcmp(yytext, "while") == 0 ||
       strcmp(yytext, "for") == 0 ||
       strcmp(yytext, "int") == 0 ||
       strcmp(yytext, "char") == 0 ||
       strcmp(yytext, "float") == 0 ||
       strcmp(yytext, "printf") == 0) {
        counter++;
    }
}

[ \t\n]+ {/*ignore white spaces*/}
.   {/*ignore other characters*/}
%%

int main(){
    yylex();
    printf("Total no of keywords are: %d\n", counter);
}

int yywrap(){
    return 1;
}