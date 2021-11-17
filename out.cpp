#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <functional>

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

//déclaration des variables
char* ram__ram;
char* _tmp3_reg;
char* c_reg;
char* s_reg;
char* rom0_rom;
char* rom1_rom;
char* _l_2_mem;
bool _l_2_bool;
function<char*()> _l_2;
char* _my_constant_0__mem;
bool _my_constant_0__bool;
function<char*()> _my_constant_0_;
char* _my_constant_1__mem;
bool _my_constant_1__bool;
function<char*()> _my_constant_1_;
char* _my_constant_2__mem;
bool _my_constant_2__bool;
function<char*()> _my_constant_2_;
char* _tmp_mem;
bool _tmp_bool;
function<char*()> _tmp;
char* _tmp2_mem;
bool _tmp2_bool;
function<char*()> _tmp2;
char* _tmp3_mem;
bool _tmp3_bool;
function<char*()> _tmp3;
char* c_mem;
bool c_bool;
function<char*()> c;
char* o_mem;
bool o_bool;
function<char*()> o;
char* ra_mem;
bool ra_bool;
function<char*()> ra;
char* ram__mem;
bool ram__bool;
function<char*()> ram_;
char* rom0_mem;
bool rom0_bool;
function<char*()> rom0;
char* rom1_mem;
bool rom1_bool;
function<char*()> rom1;
char* rom__mem;
bool rom__bool;
function<char*()> rom_;
char* s_mem;
bool s_bool;
function<char*()> s;
char* sram_mem;
bool sram_bool;
function<char*()> sram;
char* u_mem;
bool u_bool;
function<char*()> u;


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

    //initialisation des roms
	create_mem(&rom0_rom,1,2);
	init_rom(rom0_rom,"rom0",hexa,1,2);
	create_mem(&rom1_rom,1,2);
	init_rom(rom1_rom,"rom1",hexa,1,2);


    //creation des rams
	create_mem(&ram__ram,1,4);


    //creation des variables
	create_mem(&_l_2_mem,1,1);
	create_mem(&_my_constant_0__mem,1,1);
	create_mem(&_my_constant_1__mem,1,1);
	create_mem(&_my_constant_2__mem,1,1);
	create_mem(&_tmp_mem,1,1);
	create_mem(&_tmp2_mem,1,1);
	create_mem(&_tmp3_mem,1,1);
	create_mem(&c_mem,1,1);
	create_mem(&o_mem,1,4);
	create_mem(&ra_mem,1,1);
	create_mem(&ram__mem,1,4);
	create_mem(&rom0_mem,1,2);
	create_mem(&rom1_mem,1,2);
	create_mem(&rom__mem,1,2);
	create_mem(&s_mem,1,1);
	create_mem(&sram_mem,1,2);
	create_mem(&u_mem,1,1);


    //creation des registres
	create_mem(&_tmp3_reg,1,1);
	create_mem(&c_reg,1,1);
	create_mem(&s_reg,1,1);


    //equations
	_my_constant_0_=([](){
		if(!_my_constant_0__bool) of_string(_my_constant_0__mem,1,"0");
		_my_constant_0__bool=true;
		return _my_constant_0__mem;
	});
	ram_=([](){
		if(!ram__bool) copy(ram__ram,ram__mem,to_int(_my_constant_0_(),0,1),0,4);
		ram__bool=true;
		return ram__mem;
	});
	ra=([](){
		if(!ra_bool) op_select(ra_mem,1,ram_());
		ra_bool=true;
		return ra_mem;
	});
	u=([](){
		if(!u_bool) copy(_tmp3_reg,u_mem,0,0,1);
		u_bool=true;
		return u_mem;
	});
	s=([](){
		if(!s_bool) copy(c_reg,s_mem,0,0,1);
		s_bool=true;
		return s_mem;
	});
	_l_2=([](){
		if(!_l_2_bool) copy(s_reg,_l_2_mem,0,0,1);
		_l_2_bool=true;
		return _l_2_mem;
	});
	_tmp=([](){
		if(!_tmp_bool) op_and(_tmp_mem,s(),_l_2(),1);
		_tmp_bool=true;
		return _tmp_mem;
	});
	_tmp2=([](){
		if(!_tmp2_bool) op_xor(_tmp2_mem,u(),_tmp(),1);
		_tmp2_bool=true;
		return _tmp2_mem;
	});
	_tmp3=([](){
		if(!_tmp3_bool) op_xor(_tmp3_mem,_tmp2(),ra(),1);
		_tmp3_bool=true;
		return _tmp3_mem;
	});
	sram=([](){
		if(!sram_bool) op_slice(sram_mem,2,3,ram_());
		sram_bool=true;
		return sram_mem;
	});
	rom0=([](){
		if(!rom0_bool) copy(rom0_rom,rom0_mem,to_int(u(),0,1),0,2);
		rom0_bool=true;
		return rom0_mem;
	});
	rom1=([](){
		if(!rom1_bool) copy(rom1_rom,rom1_mem,to_int(u(),0,1),0,2);
		rom1_bool=true;
		return rom1_mem;
	});
	rom_=([](){
		if(!rom__bool) op_mux(rom__mem,s(),rom0(),rom1(),2);
		rom__bool=true;
		return rom__mem;
	});
	o=([](){
		if(!o_bool) op_concat(o_mem,sram(),rom_(),2,2);
		o_bool=true;
		return o_mem;
	});
	c=([](){
		if(!c_bool) op_not(c_mem,_l_2(),1);
		c_bool=true;
		return c_mem;
	});
	_my_constant_1_=([](){
		if(!_my_constant_1__bool) of_string(_my_constant_1__mem,1,"1");
		_my_constant_1__bool=true;
		return _my_constant_1__mem;
	});
	_my_constant_2_=([](){
		if(!_my_constant_2__bool) of_string(_my_constant_2__mem,1,"0");
		_my_constant_2__bool=true;
		return _my_constant_2__mem;
	});


    while(step!=0)
    {
        step--;
        //inputs
		_l_2_bool=false;
		_my_constant_0__bool=false;
		_my_constant_1__bool=false;
		_my_constant_2__bool=false;
		_tmp_bool=false;
		_tmp2_bool=false;
		_tmp3_bool=false;
		c_bool=false;
		o_bool=false;
		ra_bool=false;
		ram__bool=false;
		rom0_bool=false;
		rom1_bool=false;
		rom__bool=false;
		s_bool=false;
		sram_bool=false;
		u_bool=false;


        //actualisation des rams
		if(*_my_constant_1_()){
			copy(o(),ram__ram,0,to_int(_my_constant_2_(),0,1),4);
		}


        //outputs
		cout<<"o : ";
		print(o(),0,4);


        //actualisation des registres
		copy(_tmp3(),_tmp3_reg,0,0,1);
		copy(c(),c_reg,0,0,1);
		copy(s(),s_reg,0,0,1);

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