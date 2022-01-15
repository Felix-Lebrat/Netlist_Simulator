#include "afficheur.h"
#include <cmath>
#include <iostream>

using namespace std;

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