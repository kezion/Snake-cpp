#include "FoodType.h"
#include <cmath>

normalFood::normalFood(Point poz) : Food(poz) {}
char normalFood::getSymbol(const Point &snakeHead) const {
    return '*';
}

int normalFood::getPoints() const {
    return 1;
}

rareFood::rareFood(Point poz) : Food(poz) {}

char rareFood::getSymbol(const Point &snakeHead) const {
    return '$';
}

int rareFood::getPoints() const {
    return 5;
}

toxicFood::toxicFood(Point poz, int duration) : Food(poz), movesLeft(duration) {}

char toxicFood::getSymbol(const Point &snakeHead) const {
    int distance = abs(pozycja.getX() - snakeHead.getX()) + abs(pozycja.getY() - snakeHead.getY());
    if (distance <=3) {
        return 'X';
    }
    else {
        return '*';
    }
}


int toxicFood::getPoints() const {
    return 0;
}

bool toxicFood::czyTrujace() const {
    return true;
}

void toxicFood::update() {
    if (movesLeft > 0) {
        movesLeft--;
    }
}

bool toxicFood::czyWygaslo() const {
    return movesLeft <= 0;
}
