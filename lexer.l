%{
    #include "structures.h"
    #include "parser.h"
    #include <stdlib.h>
    #include <string.h>
    #include <iostream>
    #include <map>

    using namespace std;

    int no_ligne=1;
    int no_colonne=0;
    #define YY_USER_ACTION \
        for(int i=0;yytext[i]!='\0';i++)\
        {\
            if(yytext[i]=='\n')\
            {\
                no_colonne=0;\
                no_ligne++;\
            }\
            else\
                no_colonne++;\
        }\
        yylloc.first_line=no_ligne;\
        yylloc.last_line=no_ligne;\
        yylloc.first_column=no_colonne-strlen(yytext);\
        yylloc.last_column=no_colonne;
    map<string,int> mots_clefs=
    {
        {"INPUT",INPUT},
        {"OUTPUT",OUTPUT},
        {"VAR",VAR},
        {"IN",IN},
        {"NOT",NOT},
        {"AND",AND},
        {"NAND",NAND},
        {"OR",OR},
        {"XOR",XOR},
        {"MUX",MUX},
        {"REG",REG},
        {"CONCAT",CONCAT},
        {"SELECT",SELECT},
        {"SLICE",SLICE},
        {"ROM",ROM},
        {"RAM",RAM},
        {"CLOCK",CLOCK},
        {"DISPLAY",DISPLAY}
    };
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

{id} {
    auto it=mots_clefs.find(string(yytext));
    if(it==mots_clefs.end())
    {
        yylval.str=(char*)malloc(strlen(yytext)+1);
        strcpy(yylval.str,yytext);
        return ID;
    }
    switch(it->second)
    {
    case INPUT:
    case OUTPUT:
    case VAR:
    case IN:
    case RAM:
    case CLOCK:
    case DISPLAY:
        return it->second;
    case NOT:
    case REG:
        yylval.i=it->second;
        return UNOP;
    case AND:
    case NAND:
    case OR:
    case XOR:
    case CONCAT:
        yylval.i=it->second;
        return BINOP;
    case MUX:
        yylval.i=MUX;
        return MUX;
    case SELECT:
        yylval.i=SELECT;
        return SELECT;
    case SLICE:
    case ROM:
        yylval.i=it->second;
        return TERNOP;
    }
    return EOF;
}
{num} {yylval.str=yytext;return NUM;}
= {return EQUAL;}
: {return DP;}
{whitespace}

%%