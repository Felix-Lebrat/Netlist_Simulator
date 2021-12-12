%{
    #include "structures.h"
    #include "parser.h"
    #include <stdlib.h>
    #include <string.h>
    #include <iostream>
%}

%option noyywrap

%x ccommentaire
%x cppcommentaire

num ([0-9]+[0-9]*)
whitespace [ \n\t',']
id _?[a-zA-Z](_|[a-zA-Z0-9])*
%%

"\/\*" {BEGIN(ccommentaire);}
<ccommentaire>"\*\/" {BEGIN(INITIAL);}
<ccommentaire>.|\n
<ccommentaire><<EOF>> {
    std::cerr<<"commentaire non fermé"<<std::endl;
    exit(1);
}

"\/\/" {BEGIN(cppcommentaire);}
<cppcommentaire>"\n" {BEGIN(INITIAL);}
<cppcommentaire>.

INPUT {return INPUT;}
OUTPUT {return OUTPUT;}
VAR {return VAR;}
IN {return IN;}
NOT {yylval.i=NOT;return UNOP;}
AND {yylval.i=AND;return BINOP;}
NAND {yylval.i=NAND;return BINOP;}
OR {yylval.i=OR;return BINOP;}
XOR {yylval.i=XOR;return BINOP;}
MUX {yylval.i=MUX;return MUX;}
REG {yylval.i=REG;return UNOP;}
CONCAT {yylval.i=CONCAT;return BINOP;}
SELECT {yylval.i=SELECT;return SELECT;}
SLICE {yylval.i=SLICE;return TERNOP;}
ROM {yylval.i=ROM;return TERNOP;}
RAM {return RAM;}
{id} {yylval.str=(char*)malloc(strlen(yytext)+1);strcpy(yylval.str,yytext);return ID;}
{num} {yylval.str=yytext;return NUM;}
= {return EQUAL;}
: {return DP;}
{whitespace}

%%