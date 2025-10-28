%{
    #include<stdio.h>
    int yylex(void);
    int yyerror(const char *s);
%}

%token KEYWORD 