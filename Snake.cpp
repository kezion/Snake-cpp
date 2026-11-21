#include "Snake.h"

Snake::Snake(Point start, int startDlugosc) : head(start), chwilowyKierunek(Kierunek::RIGHT), shouldGrow(false) {
    for (int i = 1; i <= startDlugosc; ++i) {
        body.emplace_back(start.getX()-i, start.getY());
    }
}

void Snake::setKierunek(Kierunek newKierunek) {
    if (chwilowyKierunek == Kierunek::UP && newKierunek == Kierunek::DOWN) return;
    if (chwilowyKierunek == Kierunek::DOWN && newKierunek == Kierunek::UP) return;
    if (chwilowyKierunek == Kierunek::LEFT && newKierunek == Kierunek::RIGHT) return;
    if (chwilowyKierunek == Kierunek::RIGHT && newKierunek == Kierunek::LEFT) return;

    chwilowyKierunek = newKierunek;
}

void Snake::ruch() {
    body.insert(body.begin(), head);

    if (!shouldGrow) {
        body.pop_back();
    }
    else {
        shouldGrow = false;
    }

    int nextX = head.getX();
    int nextY = head.getY();

    switch (chwilowyKierunek) {
        case Kierunek::UP: nextY -= 1; break;
        case Kierunek::DOWN: nextY += 1; break;
        case Kierunek::LEFT: nextX -= 1; break;
        case Kierunek::RIGHT: nextX += 1; break;
    }
    head.setX(nextX);
    head.setY(nextY);
}

void Snake::grow() {
    shouldGrow = true;
}

Point Snake::getHead() const {
    return head;
}

const vector<Point>& Snake::getBody() const {
    return body;
}

bool Snake::selfKolizja() const {
    for (const auto& segment : body) {
        if (head == segment)  {
            return true;
        };
    }
    return false;
}

bool Snake::zajete(const Point& p) const {
    if (head == p) return true;
    for (const auto& segment : body) {
        if (segment == p) return true;
    }
    return false;
}