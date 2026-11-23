#pragma once
#include "Board.h"
#include "Snake.h"
#include "Food.h"

class Game {
private:
    Board plansza;
    Snake waz;
    Food* jedzenie;

    int wynik;
    bool koniecGry;
    bool wygrana;

    void generujJedzenie();
    void obsluzWejscie();
    void aktualizuj();
public:
    Game(int szerokosc =25,int wysokosc=15);
    ~Game();
    void run();

};

