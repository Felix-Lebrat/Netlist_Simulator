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
    catch(const string& s)
    {
        cerr<<"variable "<<s<<" mal déclarée"<<endl;
        exit(EXIT_FAILURE);
    }

    cerr<<"production de code terminée"<<endl;

    system("g++ -w -o out out.cpp -lncurses");
    
    return 0;
}

void write_cpp(Program *p,string skeleton_file)
{
    stringstream code[10];
    /* code contient le code à insérer aux différentes positions marquées par des # dans le fichier skeleton :
        0 la déclaration des variables
        1 l'initialisation des roms
        2 la creation des rams
        3 la creation des variables
        4 la creation des registres
        5 l'actualisation des entrées
        6 l'actualisation des variables
        7 l'actualisation des rams
        8 l'actualisation des registres
        9 l'écriture des sorties
    */
    int nb_roms=0;
    map<string,int>::iterator left;
    for(int i=0;i<p->equations.size();i++)
    {
        left=p->var_dict.find(p->equations[i].left);
        if(left==p->var_dict.end())
        {
            throw p->equations[i].left;
        }
        string binop;
        code[6]<<"\t"<<left->first<<"_fun=([](){"<<endl;
        code[6]<<"\t\tif(!"<<left->first<<"_bool) ";
        if(p->equations[i].type==ID)
        {
            map<string,int>::iterator right=p->var_dict.find(p->equations[i].right[0].str);
            if(right==p->var_dict.end()||right->second!=left->second)
                throw p->equations[i].right[0].str;
            code[6]<<"copy("<<right->first<<"_fun(),"<<left->first<<"_mem,0,0,"<<right->second<<");"<<endl;
        }
        else if(p->equations[i].type==NUM)
        {
            string constant=p->constants[p->equations[i].right[0].i].value;
            if(left->second!=constant.size())
                throw left->first;
            code[6]<<"of_string("<<left->first<<"_mem,"<<left->second<<",\"";
            code[6]<<constant;
            code[6]<<"\");"<<endl;
        }
        else if(p->equations[i].type==NOT)
        {
            map<string,int>::iterator right=p->var_dict.find(p->equations[i].right[0].str);
            if(left->second!=right->second)
                throw left->first;
            code[6]<<"op_not("<<left->first<<"_mem,"<<right->first<<"_fun(),"<<right->second<<");"<<endl;
        }
        else if(p->equations[i].type==REG)
        {
            map<string,int>::iterator right=p->var_dict.find(p->equations[i].right[0].str);
            if(left->second!=right->second)
                throw left->first;
            if(p->clock==left->first) p->clock=right->first;
            if(p->display==left->first) p->display=right->first;
            code[0]<<"char* "<<right->first<<"_reg;"<<endl;
            code[4]<<"\tcreate_mem(&"<<right->first<<"_reg,0,"<<right->second<<");"<<endl;
            code[6]<<"copy("<<right->first<<"_reg,"<<left->first<<"_mem,0,0,"<<left->second<<");"<<endl;
            code[8]<<"\t\tcopy("<<right->first<<"_fun(),"<<right->first<<"_reg,0,0,"<<right->second<<");"<<endl;
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
                throw left->first;
            code[6]<<"op_concat("<<left->first<<"_mem,"<<a->first<<"_fun(),"<<b->first<<"_fun(),"<<a->second<<","<<b->second<<");"<<endl;

        }
        else if(p->equations[i].type==SELECT)
        {
            map<string,int>::iterator a=p->var_dict.find(p->equations[i].right[1].str);
            int no=p->equations[i].right[0].i;
            if(left->second!=1)
                throw left->first;
            if(a->second<=no)
                throw a->first;
            code[6]<<"op_select("<<left->first<<"_mem,"<<no<<","<<a->first<<"_fun());"<<endl;
        }
        else if(p->equations[i].type==MUX)
        {
            map<string,int>::iterator choice=p->var_dict.find(p->equations[i].right[0].str);
            map<string,int>::iterator a=p->var_dict.find(p->equations[i].right[1].str);
            map<string,int>::iterator b=p->var_dict.find(p->equations[i].right[2].str);
            if(choice->second!=1)
                throw choice->first;
            if(left->second!=a->second||left->second!=b->second)
                throw left->first;
            code[6]<<"op_mux("<<left->first<<"_mem,"<<choice->first<<"_fun(),"<<a->first<<"_fun(),"<<b->first<<"_fun(),"<<left->second<<");"<<endl;

        }
        else if(p->equations[i].type==SLICE)
        {
            int i1=p->equations[i].right[0].i;
            int i2=p->equations[i].right[1].i;
            map<string,int>::iterator a=p->var_dict.find(p->equations[i].right[2].str);
            if(left->second!=i2-i1+1)
                throw left->first;
            if(a->second<=i2||i1<0)
                throw a->first;
            code[6]<<"op_slice("<<left->first<<"_mem,"<<i1<<","<<i2<<","<<a->first<<"_fun());"<<endl;

        }
        else if(p->equations[i].type==ROM)
        {
            int addr_size=p->equations[i].right[0].i;
            int word_size=p->equations[i].right[1].i;
            map<string,int>::iterator read_addr=p->var_dict.find(p->equations[i].right[2].str);
            if(left->second!=word_size)
                throw left->first;
            if(read_addr->second!=addr_size)
                throw read_addr->first;
            code[0]<<"char* "<<left->first<<"_rom;"<<endl;
            code[1]<<"\tcreate_mem(&"<<left->first<<"_rom,"<<addr_size<<","<<word_size<<");"<<endl;
            code[1]<<"\tinit_rom("<<left->first<<"_rom,\""<<left->first<<"\",hexa,"<<addr_size<<","<<word_size<<");"<<endl;
            code[6]<<"copy("<<left->first<<"_rom,"<<left->first<<"_mem,to_int("<<read_addr->first<<"_fun(),0,"<<addr_size<<"),0,"<<word_size<<");"<<endl;

        }
        else if(p->equations[i].type==RAM)
        {
            int addr_size=p->equations[i].right[0].i;
            int word_size=p->equations[i].right[1].i;
            code[4]<<"int "<<left->first<<"_addr_size="<<addr_size<<";\n";
            code[4]<<"int "<<left->first<<"_word_size="<<word_size<<";\n";
            map<string,int>::iterator read_addr=p->var_dict.find(p->equations[i].right[2].str);
            if(left->second!=word_size)
                throw left->first;
            if(read_addr->second!=addr_size)
                throw read_addr->first;
            code[0]<<"char* "<<left->first<<"_ram;"<<endl;
            code[2]<<"\tcreate_mem(&"<<left->first<<"_ram,"<<addr_size<<","<<word_size<<");"<<endl;
            code[6]<<"copy("<<left->first<<"_ram,"<<left->first<<"_mem,to_int("<<read_addr->first<<"_fun(),0,"<<addr_size<<"),0,"<<word_size<<");"<<endl;

            map<string,int>::iterator write_enable=p->var_dict.find(p->equations[i].right[3].str);
            map<string,int>::iterator write_addr=p->var_dict.find(p->equations[i].right[4].str);
            map<string,int>::iterator write_data=p->var_dict.find(p->equations[i].right[5].str);
            if(write_enable->second!=1)
                throw write_enable->first;
            if(write_addr->second!=addr_size)
                throw write_addr->first;
            if(write_data->second!=word_size)
                throw write_data->first;

            code[7]<<"\t\tif(*"<<write_enable->first<<"_fun()){"<<endl;
                code[7]<<"\t\t\tcopy("<<write_data->first<<"_fun(),"<<left->first<<"_ram,0,";
                code[7]<<"to_int("<<write_addr->first<<"_fun(),0,"<<addr_size<<"),";
                code[7]<<word_size<<");"<<endl;
            code[7]<<"\t\t}"<<endl;

        }
        if(binop!="")
        {
            map<string,int>::iterator a=p->var_dict.find(p->equations[i].right[0].str);
            map<string,int>::iterator b=p->var_dict.find(p->equations[i].right[1].str);
            if(left->second!=a->second||left->second!=b->second)
                throw left->first;
            code[6]<<"op_"<<binop<<"("<<left->first<<"_mem,"<<a->first<<"_fun(),"<<b->first<<"_fun(),"<<left->second<<");"<<endl;
        }
        code[6]<<"\t\t"<<left->first<<"_bool=true;"<<endl;
        code[6]<<"\t\treturn "<<left->first<<"_mem;"<<endl;
        code[6]<<"\t});"<<endl;

    }
    for(map<string,int>::iterator it=p->var_dict.begin();it!=p->var_dict.end();it++)
    {
        code[0]<<"char* "<<it->first<<"_mem;"<<endl;
        code[0]<<"bool "<<it->first<<"_bool;"<<endl;
        code[0]<<"function<char*()> "<<it->first<<"_fun;"<<endl;
        code[5]<<"\t\t"<<it->first<<"_bool=false;"<<endl;
        code[3]<<"\tcreate_mem(&"<<it->first<<"_mem,0,"<<it->second<<");"<<endl;
    }

    for(int i=p->input.size()-1;i>=0;i--)
    {
        map<string,int>::iterator input=p->var_dict.find(p->input[i]);
        if(input==p->var_dict.end())
            throw p->input[i];
        code[6]<<"\t\t"<<input->first<<"_fun=[](){return "<<input->first<<"_mem;};"<<endl;
        code[5]<<"\t\twhile(!of_input("<<input->first<<"_mem,"<<input->second<<",\""<<input->first<<"\"));"<<endl;
    }

    for(int i=p->output.size()-1;i>=0;i--)
    {
        map<string,int>::iterator output=p->var_dict.find(p->output[i]);
        if(output==p->var_dict.end())
            throw p->output[i];
        code[9]<<"\t\tif(!meta) cout<<\""<<output->first<<" : \";\n"<<"\t\tprint("<<output->first<<"_fun(),0,"<<output->second<<",meta);"<<endl;
    }

    if(p->meta)
    {
        code[4]<<"bool meta=true;\n";
        code[4]<<"char* clock_registre="<<p->clock<<"_reg;\n";
        code[4]<<"char* display="<<p->display<<"_reg;\n";
        code[4]<<"int reg_size="<<p->var_dict.find(p->clock)->second<<";\n";
        code[4]<<"int ram_size_word="<<p->ram<<"_word_size;\n";
        code[4]<<"int ram_size_addr="<<p->ram<<"_addr_size;\n";
        code[4]<<"char* ram="<<p->ram<<"_ram;\n";
    }
    else
    {
        code[4]<<"bool meta=false;\n";
        code[4]<<"char* clock_registre;\n";
        code[4]<<"char* display;\n";
        code[4]<<"int reg_size;\n";
        code[4]<<"int ram_size_word;\n";
        code[4]<<"int ram_size_addr;\n";
        code[4]<<"char* ram;\n";
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

    int tab_correspondance[10]={0,1,2,3,4,6,5,7,9,8};
    while(file.get(buff))
    {
        if(buff=='$')
        {
            output_file<<code[tab_correspondance[i]].str();
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