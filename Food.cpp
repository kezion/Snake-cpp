#include "Food.h"

Food::Food(Point poz) : pozycja(poz) {}

Point Food::getPozycja() const {
    return pozycja;
}

void Food::setPozycja(Point poz) {
    pozycja = poz;
}
bool Food::czyTrujace() const {
    return false;
}

void Food::update() {
}

bool Food::czyWygaslo() const {
    return false;
}