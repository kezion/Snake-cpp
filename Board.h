#pragma once
#include <vector>
#include "Point.h"
#include "Food.h"

class Board {
private:
    int szerokosc,wysokosc;
public:
    Board(int s=25, int w=20);

    int getSzerokosc() const;
    int getWysokosc() const;

    bool pozaBoard(const Point& p) const;

    void tworzenie(int wynik, const Point& head, const vector<Point>& body,const Food& food) const;

};