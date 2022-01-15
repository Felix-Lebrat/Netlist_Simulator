#include "afficheur.h"
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>

using namespace std;

char convert(int val)
{
    char tab[10]={
        0b0111111,
        0b0000110,
        0b1011011,
        0b1001111,
        0b1100110,
        0b1101101,
        0b1111101,
        0b0000111,
        0b1111111,
        0b1101111
    };
    return tab[val];
}

int main()
{
    initscr();
    start_color();
    init_pair(1,COLOR_GREEN,COLOR_RED);
    vector<char> data=
    {
        convert(1),convert(2),
        convert(3),convert(4),
        convert(5),convert(6),
        convert(1),convert(4),
        convert(0),convert(1),
        convert(2),convert(0),convert(2),convert(2),
    };
    for(int i=0;i<100000;i++)
    {
        horloge(Coord(9,9),data.data());
        refresh();
    }
    endwin();

    return 0;
}
