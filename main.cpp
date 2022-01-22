//#include "parser.h"
#include "structures.h"
//#include "lexer.h"
#include <iostream>
#include "graph.h"
#include <vector>
#include "schedule.h"
#include <map>
#include "parser.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <exception>
//#define DEBUG

using namespace std;

void check_variables(Program *p)
{
    map<string,int>::iterator it;
    for(int i=0;i<p->var.size();i++)
    {
        it=p->var_dict.find(p->var[i].id);
        if(it!=p->var_dict.end()&&it->second!=p->var[i].size)
        {
            cerr<<"la variable "<<it->first<<" a plusieurs definitions incoherentes"<<endl;
            exit(EXIT_FAILURE);
        }
        p->var_dict[p->var[i].id]=p->var[i].size;
    }
}


void write_cpp(Program *p,string skeleton_file);

class Erreur:public exception
{
public:
    Erreur(string message) throw():m_message(new string(message+" mal déclarée\n")){};

    virtual const char* what() const throw()
    {
        return m_message->c_str();
    };

    ~Erreur()
    {
        delete m_message;
    };
private:
    string *m_message;
};

int main(int argc,char **argv)
{
    if(argc==1)
    {
        cerr<<"pas de fichier spécifié"<<endl;
        exit(EXIT_FAILURE);
    }
    Program *p=parse(argv[1]);

    check_variables(p);
    schedule(p);
    try
    {
        write_cpp(p,"skeleton.cpp");
    }
    catch(const Erreur& e)
    {
        cerr<<e.what()<<endl;
        exit(EXIT_FAILURE);
    }

    cerr<<"production de code terminée"<<endl;

    system("g++ -g -w -o out out.cpp -lncurses");
    
    return 0;
}


void write_cpp(Program *p,string skeleton_file)
{
    stringstream code[10];
    /* code contient le code à insérer aux différentes positions marquées par des # dans le fichier skeleton :
        0 la déclaration des variables
        1 l'initialistaion des variables
        2 l'écriture des sorties
        3 l'actualisation des rams
        4 l'actualisation des registres
    */
    int nb_roms=0;
    for(int i=p->input.size()-1;i>=0;i--)
    {
        map<string,int>::iterator input=p->var_dict.find(p->input[i]);
        if(input==p->var_dict.end())
            throw Erreur(p->input[i]);
        code[0]<<"Input "<<input->first<<"_;\n";
        code[1]<<input->first<<"_=Input(\""<<input->first<<"\","<<input->second<<");\n";
    }
    map<string,int>::iterator left;
    for(int i=0;i<p->equations.size();i++)
    {
        left=p->var_dict.find(p->equations[i].left);
        if(left==p->var_dict.end())
        {
            throw Erreur(p->equations[i].left);
        }
        string binop;
        if(p->equations[i].type==ID)
        {
            map<string,int>::iterator right=p->var_dict.find(p->equations[i].right[0].str);
            if(right==p->var_dict.end()||right->second!=left->second)
                throw Erreur(p->equations[i].right[0].str);
            code[0]<<"Id "<<left->first<<"_;\n";
            code[1]<<left->first<<"_=Id(0,";
            code[1]<<right->second<<",&"<<right->first<<"_);\n";
        }
        else if(p->equations[i].type==NUM)
        {
            string constant=p->constants[p->equations[i].right[0].i].value;
            if(left->second!=constant.size())
                throw Erreur(left->first);
            code[0]<<"Constante "<<left->first<<"_;\n";
            code[1]<<left->first<<"_=Constante(";
            code[1]<<left->second<<",\""<<constant<<"\");\n";
        }
        else if(p->equations[i].type==NOT)
        {
            map<string,int>::iterator right=p->var_dict.find(p->equations[i].right[0].str);
            if(left->second!=right->second)
                throw Erreur(left->first);
            code[0]<<"Not "<<left->first<<"_;\n";
            code[1]<<left->first<<"_=Not(";
            code[1]<<left->second<<",&"<<right->first<<"_);\n";
        }
        else if(p->equations[i].type==REG)
        {
            map<string,int>::iterator right=p->var_dict.find(p->equations[i].right[0].str);
            if(left->second!=right->second)
                throw Erreur(left->first);
            code[0]<<"Reg "<<left->first<<"_;\n";
            code[1]<<left->first<<"_=Reg(";
            code[1]<<left->second<<",&"<<right->first<<"_);\n";
            code[4]<<left->first<<"_.actualiser();\n";
        }
        else if(p->equations[i].type==AND)
        {
            binop="and";
        }
        else if(p->equations[i].type==NAND)
        {
            binop="nand";
        }
        else if(p->equations[i].type==OR)
        {
            binop="or";
        }
        else if(p->equations[i].type==XOR)
        {
            binop="xor";
        }
        else if(p->equations[i].type==CONCAT)
        {
            map<string,int>::iterator a=p->var_dict.find(p->equations[i].right[0].str);
            map<string,int>::iterator b=p->var_dict.find(p->equations[i].right[1].str);
            if(left->second!=a->second+b->second)
                throw Erreur(left->first);
            code[0]<<"Concat "<<left->first<<"_;\n";
            code[1]<<left->first<<"_=Concat(&";
            code[1]<<a->first<<"_,&"<<b->first<<"_);\n";
        }
        else if(p->equations[i].type==SELECT)
        {
            map<string,int>::iterator a=p->var_dict.find(p->equations[i].right[1].str);
            int no=p->equations[i].right[0].i;
            if(left->second!=1)
                throw Erreur(left->first);
            if(a->second<=no)
                throw Erreur(a->first);
            code[0]<<"Select "<<left->first<<"_;\n";
            code[1]<<left->first<<"_=Select(&";
            code[1]<<a->first<<"_,"<<no<<");\n";
        }
        else if(p->equations[i].type==MUX)
        {
            map<string,int>::iterator choice=p->var_dict.find(p->equations[i].right[0].str);
            map<string,int>::iterator a=p->var_dict.find(p->equations[i].right[1].str);
            map<string,int>::iterator b=p->var_dict.find(p->equations[i].right[2].str);
            if(choice->second!=1)
                throw Erreur(choice->first);
            if(left->second!=a->second||left->second!=b->second)
                throw Erreur(left->first);
            code[0]<<"Mux "<<left->first<<"_;\n";
            code[1]<<left->first<<"_=Mux(&";
            code[1]<<choice->first<<"_,&"<<a->first<<"_,&"<<b->first<<"_);\n";
        }
        else if(p->equations[i].type==SLICE)
        {
            int i1=p->equations[i].right[0].i;
            int i2=p->equations[i].right[1].i;
            map<string,int>::iterator a=p->var_dict.find(p->equations[i].right[2].str);
            if(left->second!=i2-i1+1)
                throw Erreur(left->first);
            if(a->second<=i2||i1<0)
                throw Erreur(a->first);
            code[0]<<"Slice "<<left->first<<"_;\n";
            code[1]<<left->first<<"_=Slice(&";
            code[1]<<a->first<<"_,"<<i1<<","<<i2<<");\n";
        }
        else if(p->equations[i].type==ROM)
        {
            int addr_size=p->equations[i].right[0].i;
            int word_size=p->equations[i].right[1].i;
            map<string,int>::iterator read_addr=p->var_dict.find(p->equations[i].right[2].str);
            if(left->second!=word_size)
                throw Erreur(left->first);
            if(read_addr->second!=addr_size)
                throw Erreur(read_addr->first);
            code[0]<<"Rom "<<left->first<<"_;\n";
            code[1]<<left->first<<"_=Rom(";
            code[1]<<word_size<<",\""<<left->first<<"\",hexa,&"<<read_addr->first<<"_);\n";

        }
        else if(p->equations[i].type==RAM)
        {
            int addr_size=p->equations[i].right[0].i;
            int word_size=p->equations[i].right[1].i;
            map<string,int>::iterator read_addr=p->var_dict.find(p->equations[i].right[2].str);
            if(left->second!=word_size)
                throw Erreur(left->first);
            if(read_addr->second!=addr_size)
                throw Erreur(read_addr->first);

            map<string,int>::iterator write_enable=p->var_dict.find(p->equations[i].right[3].str);
            map<string,int>::iterator write_addr=p->var_dict.find(p->equations[i].right[4].str);
            map<string,int>::iterator write_data=p->var_dict.find(p->equations[i].right[5].str);
            if(write_enable->second!=1)
                throw Erreur(write_enable->first);
            if(write_addr->second!=addr_size)
                throw Erreur(write_addr->first);
            if(write_data->second!=word_size)
                throw Erreur(write_data->first);

            code[0]<<"Ram "<<left->first<<"_;\n";
            code[1]<<left->first<<"_=Ram(&";
            code[1]<<read_addr->first<<"_,&"<<write_enable->first<<"_,&";
            code[1]<<write_addr->first<<"_,&"<<write_data->first<<"_,";
            code[1]<<left->second<<");\n";

            code[3]<<left->first<<"_.actualiser();\n";
        }
        if(binop!="")
        {
            map<string,int>::iterator a=p->var_dict.find(p->equations[i].right[0].str);
            map<string,int>::iterator b=p->var_dict.find(p->equations[i].right[1].str);
            if(left->second!=a->second||left->second!=b->second)
                throw Erreur(left->first);
            code[0]<<"Binop "<<left->first<<"_;\n";
            code[1]<<left->first<<"_=Binop(&";
            code[1]<<a->first<<"_,&"<<b->first<<"_,\'"<<binop[0]<<"\');\n";
        }
    }


    for(int i=p->output.size()-1;i>=0;i--)
    {
        map<string,int>::iterator output=p->var_dict.find(p->output[i]);
        if(output==p->var_dict.end())
            throw Erreur(p->output[i]);
        code[2]<<"\t\tprint("<<output->first<<"_.val(),0,"<<output->second<<",meta);"<<endl;
        code[2]<<"\t\tif(!meta) cout<<\"("<<output->first<<")\\n\";\n";
    }

    if(p->meta)
    {
        code[1]<<"bool meta=true;\n";
        code[1]<<"Reg* clock_registre=&"<<p->clock<<"_;\n";
        code[1]<<"Reg* display=&"<<p->display<<"_;\n";
        code[1]<<"Ram* ram=&"<<p->ram<<"_;\n";
    }
    else
    {
        code[1]<<"bool meta=false;\n";
        code[1]<<"Reg* clock_registre;\n";
        code[1]<<"Reg* display;\n";
        code[1]<<"Ram* ram;\n";
    }

    ifstream file(skeleton_file);
    if(!file)
    {
        cerr<<"erreur lors de l'ouverture de "<<skeleton_file<<endl;
        exit(EXIT_FAILURE);
    }
    char buff;
    int i=0;
    ofstream output_file("out.cpp");
    if(!output_file)
    {
        cerr<<"erreur lors de l'ouverture de out.cpp";
        exit(EXIT_FAILURE);
    }

    while(file.get(buff))
    {
        if(buff=='$')
        {
            output_file<<code[i].str();
            i++;
        }
        else
        {
            output_file.put(buff);
        }
    }
    file.close();
    output_file.close();
}