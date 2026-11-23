#pragma once
#include "Food.h"

class normalFood : public Food {
public:
    normalFood(Point poz);
    char getSymbol(const Point& snakeHead) const override;
    int getPoints() const override;
};

class rareFood : public Food {
public:
    rareFood(Point poz);
    char getSymbol(const Point& snakeHead) const override;
    int getPoints() const override;
};

class toxicFood : public Food {
private:
    int movesLeft;
public:
    toxicFood(Point poz, int duration=25);
    char getSymbol(const Point& snakeHead) const override;
    int getPoints() const override;
    bool czyTrujace() const override;
    void update() override;
    bool czyWygaslo() const override;
};