#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <functional>
#include <ctime>
#include <cmath>
#include <ncurses.h>

using namespace std;

bool get_bit(char *mem,int no);

void set_bit(char *mem,int no,bool val);

void copy(char *src,char *dest,int src_addr,int dest_addr,int word_size);

void create_mem(char **mem,int addr_size,int word_size);

int to_int(char *mem,int addr,int word_size);

void of_int(char *mem,int addr,int word_size,int i);

void print(char *mem,int addr,int word_size,bool meta);

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

//l'horloge
struct Coord
{
        Coord():x(0),y(0){};
        Coord(double x,double y):x(x),y(y){};

        double x;
        double y;
};

Coord operator+(Coord const& a,Coord const& b);
Coord operator-(Coord const& a,Coord const& b);
Coord operator*(double const& a,Coord const& b);

void setPixel(Coord pos);

void segment(Coord a,Coord b);

const Coord segments[7][2]=
{
    {Coord(0,1),Coord(0,4)},
    {Coord(1,5),Coord(4,5)},
    {Coord(6,5),Coord(9,5)},
    {Coord(10,4),Coord(10,1)},
    {Coord(9,0),Coord(6,0)},
    {Coord(4,0),Coord(1,0)},
    {Coord(5,1),Coord(5,4)}
};

void afficheur(Coord pos,char val);

void horloge(Coord pos,char* data);

//déclaration des variables
$

int main(int argc,char **argv)
{

    int step=-1;
    bool hexa=false;
    int clock=0;
    char clock_data[14];

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
$

    //creation des rams
$

    //creation des variables
$

    //creation des registres
$

    //equations
$

    if(meta)
    {
        initscr();
        start_color();
        init_pair(1,COLOR_GREEN,COLOR_GREEN);
    }
    while(step!=0)
    {
        step--;
        //inputs
$

        //actualisation des rams
$

        //outputs
$

        if(meta)
        {
            if(clock!=time(0))
            {
                clock=time(0);
                of_int(clock_registre,0,reg_size,clock);
            }

            int disp=to_int(display,0,reg_size);
            if(disp!=0)
            {
                for(int i=0;i<14;i++)
                {   
                    clock_data[i]=int(
                        (to_int(ram,
                        (disp&((1<<ram_size_addr)-1))+i,//on selectionne les derniers bits pour l'adresse
                        ram_size_word))
                        &((1<<7)-1));//7 bits d'information
                }
                horloge(Coord(9,9),clock_data);
                of_int(display,0,reg_size,0);
            }
        }

        //actualisation des registres
$
        if(meta)
        {
            refresh();
        }

    }

    if(meta) endwin();
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

void of_int(char *mem,int addr,int word_size,int i)
{
    for(int k=word_size-1;k>=0;k--)
    {
        set_bit(mem,addr*word_size+k,i%2);
        i/=2;
    }
}

void print(char *mem,int addr,int word_size,bool meta)
{
    if(meta) move(0,0);
    for(int i=0;i<word_size;i++)
    {
        if(meta)
            printw("%d",get_bit(mem,addr*word_size+i));
        else
            cout<<get_bit(mem,addr*word_size+i);
    }
    if(!meta) cout<<endl;
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

//l'horloge
Coord operator+(Coord const& a,Coord const& b)
{
    return Coord(a.x+b.x,a.y+b.y);
}

Coord operator*(double const& a,Coord const& b)
{
    return Coord(a*b.x,a*b.y);
}

Coord operator-(Coord const& a,Coord const& b)
{
    return a+(-1)*b;
}

void setPixel(Coord pos)
{
    mvaddch(int(pos.x),int(2*pos.y),' '|COLOR_PAIR(1));    
    mvaddch(int(pos.x),int(2*pos.y+1),' '|COLOR_PAIR(1));    
}

void segment(Coord a,Coord b)
{
    Coord vect;
    Coord dir(b.x-a.x,b.y-a.y);
    Coord pos=a;
    double norm(sqrt(dir.x*dir.x+dir.y*dir.y));
    dir.x/=norm;
    dir.y/=norm;
    while(norm>0.9)
    {
        setPixel(pos);

        pos=pos+dir;

        vect=b-pos;

        norm=vect.x*vect.x+vect.y*vect.y;
    }
    setPixel(pos);
}

void afficheur(Coord pos,char val)
{
    for(int i=0;i<7;i++)
    {
        if(val%2)
        {
            segment(segments[i][0]+pos,segments[i][1]+pos);
        }
        val/=2;
    }
}

void horloge(Coord pos,char* data)
{
    Coord curr_pos=pos+Coord(0,10);

    for(int i=0;i<3;i++)
    {
        afficheur(curr_pos,data[2*i]);
        curr_pos=curr_pos+Coord(0,7);
        afficheur(curr_pos,data[2*i+1]);
        curr_pos=curr_pos+Coord(0,7);
        if(i!=2)
        {
            setPixel(curr_pos+Coord(3,0));
            setPixel(curr_pos+Coord(7,0));
            curr_pos=curr_pos+Coord(0,2);
        }
    }

    curr_pos=pos+Coord(13,0);
    for(int i=3;i<6;i++)
    {
        afficheur(curr_pos,data[2*i]);
        curr_pos=curr_pos+Coord(0,7);
        afficheur(curr_pos,data[2*i+1]);
        curr_pos=curr_pos+Coord(0,7);
        if(i==5)
        {
            i++;
            afficheur(curr_pos,data[2*i]);
            curr_pos=curr_pos+Coord(0,7);
            afficheur(curr_pos,data[2*i+1]);
            curr_pos=curr_pos+Coord(0,7);
        }
        else
        {
            segment(curr_pos+Coord(9,0),curr_pos+Coord(1,3));            
            curr_pos=curr_pos+Coord(0,5);
        }
    }
    mvaddch(LINES-1,COLS-1,' ');
}