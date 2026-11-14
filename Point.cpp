#include "Point.h"

Point::Point(){
    x =0;
    y =0;
}
Point::Point(int x1, int y1) {
    x = x1;
    y = y1;
}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

void Point::setX(int x2) {
    x = x2;
}
void Point::setY(int y2) {
    y = y2;
}

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

bool Point::operator!=(const Point& other) const {
    return x != other.x || y != other.y;
}

ostream& operator<<(ostream& os, const Point& point) {
    os << "(" << point.x << "," << point.y << ")";
    return os;
}