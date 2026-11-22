#pragma once
#include "Point.h"


class Food {
protected:
    Point pozycja;
public:
    Food(Point poz);
    virtual ~Food() = default;

    Point getPozycja() const;
    void setPozycja(Point poz);

    virtual char getSymbol(const Point& snakeHead) const=0;
    virtual int getPoints() const=0;
    virtual bool czyTrujace() const;
    virtual void update();
    virtual bool czyWygaslo() const;

};
