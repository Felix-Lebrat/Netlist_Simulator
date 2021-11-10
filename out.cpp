#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

bool get_bit(char *mem,int no);

void set_bit(char *mem,int no,bool val);

void copy(char *src,char *dest,int src_addr,int dest_addr,int word_size);

void create_mem(char **mem,int addr_size,int word_size);

int to_int(char *mem,int addr,int word_size);

void print(char *mem,int addr,int word_size);

bool of_input(char *mem,int size,string mem_name);

void of_string(char *mem,int size,string str);

void init_rom(char *rom,char* filename,bool hexa,int addr_size,int word_size);

void op_not(char *left,char* right,int size);

void op_and(char *left,char* a,char* b,int size);

void op_nand(char *left,char* a,char* b,int size);

void op_or(char *left,char* a,char* b,int size);

void op_xor(char *left,char* a,char* b,int size);

void op_concat(char *left,char* a,char* b,int a_size,int b_size);

void op_select(char *left,int i,char *a);

void op_mux(char* left,char* choice,char *a,char *b,int size);

void op_slice(char* left,int i1,int i2,char *a);

int main(int argc,char **argv)
{
    int step=-1;
    bool hexa=false;

    for(int i=1;i<argc;i++)
    {
        if(argv[i]==string("-h"))
        {
            hexa=true;
            continue;
        }
        if(argv[i]==string("-s"))
        {
            i++;
            if(i<argc)
            {
                step=atoi(argv[i]);
            }
            continue;
        }
    }
    
    //déclaration des roms


    //initialisation des roms


    //declaration des rams


    //declaration des variables
	char* _l_2;
	create_mem(&_l_2,1,1);
	char* c;
	create_mem(&c,1,1);
	char* o;
	create_mem(&o,1,1);


    //declatation des registres
	char* c_reg;
	create_mem(&c_reg,1,1);
	char* o_reg;
	create_mem(&o_reg,1,1);


    while(step!=0)
    {
        step--;
        //inputs


        //equations
		copy(c_reg,o,0,0,1);
		copy(o_reg,_l_2,0,0,1);
		op_not(c,_l_2,1);


        //actualisation des rams


        //actualisation des registres
		copy(c,c_reg,0,0,1);
		copy(o,o_reg,0,0,1);


        //outputs
		cout<<"o : ";
		print(o,0,1);

    }
}

bool get_bit(char *mem,int no)
{
    int i=no/8;
    int k=no%8;
    char mask=1<<k;
    return mem[i] & mask;
}

void set_bit(char *mem,int no,bool val)
{
    int i=no/8;
    int k=no%8;
    char mask0=~(1<<k);
    mem[i]=mem[i]&mask0;
    char mask=val<<k;
    mem[i]=mem[i]|mask;
}

void copy(char *src,char *dest,int src_addr,int dest_addr,int word_size)
{
    for(int i=0;i<word_size;i++)
    {
        set_bit(dest,dest_addr*word_size+i,get_bit(src,src_addr*word_size+i));
    }
}

void create_mem(char **mem,int addr_size,int word_size)
{
    int size=((1<<addr_size)*word_size+7)/8;
    *mem=new char[size];
    for(int i=0;i<size;i++)
    {
        (*mem)[i]=0;
    }
}

int to_int(char *mem,int addr,int word_size)
{
    int ret=0;
    for(int i=0;i<word_size;i++)
    {
        ret*=2;
        ret+=get_bit(mem,addr*word_size+i);
    }
    return ret;
}

void print(char *mem,int addr,int word_size)
{
    for(int i=0;i<word_size;i++)
    {
        cout<<get_bit(mem,addr*word_size+i);
    }
    cout<<endl;
}

bool of_input(char *mem,int size,string mem_name)
{
    cout<<mem_name<<"?"<<endl;
    string str;
    cin>>str;
    if(size!=str.size())
    {
        cerr<<"mauvais format"<<endl;
        return false;
    }            
    for(int i=0;i<size;i++)
    {
        if(str[i]=='0'||str[i]=='1')
        {
            str[i]-='0';
            set_bit(mem,i,str[i]);
        }
        else
        {
            cerr<<"mauvais format"<<endl;
            return false;
        }
    }
    return true;
}

void of_string(char *mem,int size,string str)
{
    for(int i=0;i<size;i++)
    {
        str[i]-='0';
        set_bit(mem,i,str[i]);
    }
}

void init_rom(char *rom,char* filename,bool hexa,int addr_size,int word_size)
{
    ifstream file(filename);
    if(!file)
    {
        cerr<<"erreur lors de l'ouverture du fichiers "<<filename<<endl;
        exit(EXIT_FAILURE);
    }

    char buff;
    int nb_bits;
    int size=(1<<addr_size)*word_size;
    if(hexa)
    {
        nb_bits=4;
        if(size%4!=0)
        {
            cerr<<"format hexadecimal impossible car la taille de la rom n'est pas multiple de 4"<<endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        nb_bits=1;
    }
    int pos=0;
    while(file.get(buff)&&pos<size)
    {
        if(hexa)
        {
            if('0'<=buff && buff <= '9')
                buff-='0';
            else if ('A'<=buff && buff <='F')
                buff+=10-'A';
            else if ('a'<=buff && buff <= 'f')
                buff+=10-'a';
            else
                continue;
        }
        else
        {
            if(buff=='0' || buff=='1')
                buff-='0';
            else
                continue;
        }
        pos+=nb_bits;
        for(int i=1;i<=nb_bits;i++)
        {
            set_bit(rom,pos-i,buff%2);
            buff=buff>>1;
        }
    }
    file.close();
}

void op_not(char *left,char* right,int size)
{
    for(int i=0;i<(size+7)/8;i++)
    {
        left[i]=~right[i];
    }
}

void op_and(char *left,char* a,char* b,int size)
{
    for(int i=0;i<(size+7)/8;i++)
    {
        left[i]=a[i]&b[i];
    }
}

void op_nand(char *left,char* a,char* b,int size)
{
    for(int i=0;i<(size+7)/8;i++)
    {
        left[i]=~(a[i]&b[i]);
    }
}

void op_or(char *left,char* a,char* b,int size)
{
    for(int i=0;i<(size+7)/8;i++)
    {
        left[i]=(a[i]|b[i]);
    }
}

void op_xor(char *left,char* a,char* b,int size)
{
    for(int i=0;i<(size+7)/8;i++)
    {
        left[i]=(a[i]^b[i]);
    }
}

void op_concat(char *left,char* a,char* b,int a_size,int b_size)
{
    for(int i=0;i<a_size;i++)
    {
        set_bit(left,i,get_bit(a,i));
    }

    for(int i=0;i<b_size;i++)
    {
        set_bit(left,i+a_size,get_bit(b,i));
    }
}

void op_select(char *left,int i,char *a)
{
    set_bit(left,0,get_bit(a,i));
}

void op_mux(char* left,char* choice,char *a,char *b,int size)
{
    if(!get_bit(choice,0))
        copy(a,left,0,0,size);
    else
        copy(b,left,0,0,size);
}

void op_slice(char* left,int i1,int i2,char *a)
{
    for(int i=0;i<i2-i1+1;i++)
    {
        set_bit(left,i,get_bit(a,i+i1));
    }
}