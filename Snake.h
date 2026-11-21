#pragma once
#include "Point.h"
#include <vector>

enum class Kierunek {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

class Snake {
    private:
    Point head;
    vector<Point> body;
    Kierunek chwilowyKierunek;
    bool shouldGrow;

    public:
    Snake(Point start = Point(12,10), int startDlugosc = 3);

    void setKierunek(Kierunek newKierunek);
    void ruch();
    void grow();

    Point getHead() const;
    const vector<Point>& getBody() const;
    Kierunek getKierunek() const;

    bool selfKolizja() const;
    bool zajete(const Point& p) const;

};
