#include "Board.h"
#include <cstdlib>

Board::Board(int s1, int w1) {
    szerokosc =s1;
    wysokosc =w1;
}

int Board::getSzerokosc() const {
    return szerokosc;
}

int Board::getWysokosc() const {
    return wysokosc;
}

bool Board::pozaBoard(const Point& p) const {
    return p.getX()<0 || p.getX() >= szerokosc || p.getY()<0 || p.getY() >= wysokosc;
}
void Board::tworzenie(int wynik, const Point& head, const vector<Point>& body,const Food& food) const {
    system("cls");

    cout << "============================\n";
    cout << "   Wynik: " << wynik << "  Dlugosc: " << body.size()+1 << "\n";
    cout << "============================\n";

    cout << "+";
    for (int i =0; i < szerokosc; ++i) {
        cout << "-";
    }
    cout << "+\n";

    for (int y =0; y < wysokosc; ++y) {
        cout << "|";
        for (int x=0; x < szerokosc; ++x) {
            Point chwilowy(x,y);

            if (chwilowy==head) {
                cout << "0";
            }
            else if (chwilowy==food.getPozycja()) {
                cout << food.getSymbol(head);
            }
            else {
                bool jestWaz = false;
                for (const auto& segment : body) {
                    if (chwilowy==segment) {
                        jestWaz = true;
                        break;
                    }
                }
                if (jestWaz==true) {
                    cout << "o";
                }
                else {
                    cout << " ";
                }
            }
        }
        cout << "|\n";
    }

    cout << "+";
    for (int i =0; i < szerokosc; ++i) {
        cout << "-";
    }
    cout << "+\n\n";
    cout << "Poruszanie - [W/A/S/D] | Wyjscie - [Q]\n";


}
