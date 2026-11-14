#pragma once
#include <iostream>
using namespace std;

class Point {
private:
    int x,y;

public:
    Point();
    Point(int x1, int y1);

    int getX() const;
    int getY() const;

    void setX(int x2);
    void setY(int y2);

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;

    friend ostream& operator<<(ostream&os, const Point& p);



};
