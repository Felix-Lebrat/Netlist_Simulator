#include "schedule.h"
#include "parser.h"
#include "graph.h"
#include <iostream>

using namespace std;

vector<string> read_exp(Equation eq)
{
    vector<string> ret;
    switch (eq.type)
    {
    case ID:
    case NOT:
        ret={eq.right[0].str};
        break;
    case ROM:
    case SLICE:
        ret={eq.right[2].str};
        break;
    case SELECT:
        ret={eq.right[1].str};
        break;
    case OR:
    case AND:
    case NAND:
    case XOR:
    case CONCAT:
        ret={eq.right[0].str,eq.right[1].str};
        break;
    case MUX:
        ret={eq.right[0].str,eq.right[1].str,eq.right[2].str};
        break;
    case RAM:
        ret={eq.right[2].str};
        break;
    default:
        break;
    }
    return ret;
}

int find_equation(Program *p,string id)
{
    for(int i=0;i<p->equations.size();i++)
    {
        if(p->equations[i].left==id)
            return i;
    }
    return -1;
}

void schedule(Program *p)
{
    Graph<string> g;
    for(int i=0;i<p->var.size();i++)
        g.add_node(p->var[i].id);

    for(int i=0;i<p->equations.size();i++)
    {
        vector<string> depend=read_exp(p->equations[i]);
        for(int j=0;j<depend.size();j++)
        {
            if(p->var_dict.find(p->equations[i].left)==p->var_dict.end())
            {
                cerr<<"variable "<<p->equations[i].left<<" mal déclarée"<<endl;
                exit(EXIT_FAILURE);
            }
            if(p->var_dict.find(depend[j])==p->var_dict.end())
            {
                cerr<<"variable "<<depend[j]<<" mal déclarée"<<endl;
                exit(EXIT_FAILURE);
            }

            g.add_edge(depend[j],p->equations[i].left);
        }
    }
    vector<string> top=g.topological();
    vector<Equation> equations;
    
    for(int i=0;i<top.size();i++)
    {
        int index=find_equation(p,top[i]);
        if(index!=-1)
        {
            equations.push_back(p->equations[index]);
        }
    }
    p->equations=equations;
}
