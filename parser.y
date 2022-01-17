%{
    #include "structures.h"
    #include <stdio.h>
    #include "lexer.h"
    #include "parser.h"
    #include <map>
    #include <string>
    #include <iostream>
    #include <stdlib.h>
    #include <vector>
    void yyerror(char* s)
    {
        fprintf (stderr, "%s ligne %d colonne %d\n", s,yylloc.first_line,yylloc.first_column);
        exit(EXIT_FAILURE);
    }
    Program prg;
    int nb_contants;

    using namespace std;

    string itoa(int i)
    {
        if(i==0)
        {
            return "0";
        }

        vector<char> car;
        while(i>0)
        {
            car.push_back(char(i%10)+'0');
            i/=10;
        }
        string ret;
        for(int i=car.size()-1;i>=0;i--)
        {
            ret+=car[i];
        }
        return ret;
    }

    # define YYLLOC_DEFAULT(Cur, Rhs, N)                      \
    do  {                                                      \
    if (N)                                                  \
    {                                                     \
        (Cur).first_line   = YYRHSLOC(Rhs, 1).first_line;   \
        (Cur).first_column = YYRHSLOC(Rhs, 1).first_column; \
        (Cur).last_line    = YYRHSLOC(Rhs, N).last_line;    \
        (Cur).last_column  = YYRHSLOC(Rhs, N).last_column;  \
        }                                                     \
    else                                                    \
    {                                                     \
        (Cur).first_line   = (Cur).last_line   =            \
            YYRHSLOC(Rhs, 0).last_line;                       \
        (Cur).first_column = (Cur).last_column =            \
            YYRHSLOC(Rhs, 0).last_column;                     \
    }                                                     \
    }                                              \
    while (0)
%}
%locations

%union
{
    char* str;
    int i;
    Expression exp;
}

%token INPUT
%token OUTPUT
%token VAR
%token IN
%token <str> ID
%token <str> NUM
%token NOT
%token AND
%token NAND
%token OR
%token XOR
%token MUX
%token REG
%token CONCAT
%token SELECT
%token SLICE
%token ROM
%token RAM
%token <i> BINOP
%token <i> UNOP
%token <i> TERNOP
%token EQUAL
%token DP
%token DISPLAY
%token CLOCK

%type <i> right_equation
%type <exp> expression

%%
program:INPUT input OUTPUT output meta VAR vars IN d
;

input:%empty
    |input ID {prg.input.push_back($2);}
;

output:%empty
    |output ID{prg.output.push_back($2);}
;

meta:%empty {prg.meta=false;}
    |CLOCK ID DISPLAY ID RAM ID {prg.meta=true;prg.clock=$2;prg.display=$4;prg.ram=$6;}
;

vars:%empty
    |vars var
;

var:ID DP NUM {prg.var.push_back(Var($1,atoi($3)));}
    |ID {prg.var.push_back(Var($1,1));}
;

d:  %empty {}
    |d ID EQUAL right_equation{prg.equations[$4].left=$ID;}
;

right_equation:ID {
        Expression e;
        e.str=$1;
        prg.equations.push_back(Equation(int(ID),"",{e}));
        $$=prg.equations.size()-1;
    }
    |NUM {
        prg.constants.push_back(Const($1));
        Expression e;
        e.i=prg.constants.size()-1;
        prg.equations.push_back(Equation(NUM,"",{e}));
        $$=prg.equations.size()-1;
    }
    |UNOP expression {
        prg.equations.push_back(Equation($1,"",{$2}));
        $$=prg.equations.size()-1;
    }
    |BINOP expression expression {
        prg.equations.push_back(Equation($1,"",{$2,$3}));
        $$=prg.equations.size()-1;
    }
    |SELECT NUM expression {
        Expression e;
        e.i=atoi($2);        
        prg.equations.push_back(Equation(SELECT,"",{e,$3}));
        $$=prg.equations.size()-1;
    }
    |TERNOP NUM NUM expression {
        Expression e2;
        e2.i=atoi($2);        
        Expression e3;
        e3.i=atoi($3);        
        prg.equations.push_back(Equation($1,"",{e2,e3,$4}));
        $$=prg.equations.size()-1;
    }
    |MUX expression expression expression {
        prg.equations.push_back(Equation(MUX,"",{$2,$3,$4}));
        $$=prg.equations.size()-1;
    }
    |RAM NUM NUM expression expression expression expression {
        Expression e2;
        e2.i=atoi($2);        
        Expression e3;
        e3.i=atoi($3);        
        prg.equations.push_back(Equation(RAM,"",{e2,e3,$4,$5,$6,$7}));
        $$=prg.equations.size()-1;
    }
;

expression:NUM {
        prg.constants.push_back(Const($1));
        Expression e;
        e.i=prg.constants.size()-1;
        string buff=itoa(e.i);
        prg.equations.push_back(Equation(NUM,"_my_constant_"+buff+"_",{e}));

        prg.var.push_back(Var("_my_constant_"+buff+"_",string($1).size()));
       
        Expression e2;
        string temp("_my_constant_"+buff+"_");
        e2.str=new char[temp.size()];
        strcpy(e2.str,temp.c_str());
        $$=e2;
    }
    |ID {Expression e;e.str=$1;$$=e;}
;

%%
Program* parse(char *filename)
{
    FILE* file=NULL;
    file=fopen(filename,"r");
    if(file==NULL)
    {
        yyerror("erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    yyset_in(file);
    yyparse();

    fclose(file);
    
    return &prg;
}