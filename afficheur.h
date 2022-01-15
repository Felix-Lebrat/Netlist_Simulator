#ifndef _AFFICHEUR_H_
#define _AFFICHEUR_H_

#include <ncurses.h>

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

#endif
