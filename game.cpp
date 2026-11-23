#include "Game.h"
#include "FoodType.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <conio.h>
#include <thread>
#include <chrono>

Game::Game(int szerokosc, int wysokosc)
    : plansza(szerokosc, wysokosc),
      waz(Point(szerokosc / 2, wysokosc / 2)),
      jedzenie(nullptr),
      wynik(0),
      koniecGry(false),
      wygrana(false) {
    srand(static_cast<unsigned int>(time(nullptr)));
    generujJedzenie();
}

Game::~Game() {
    delete jedzenie;
}

void Game::generujJedzenie() {
    delete jedzenie;
    jedzenie = nullptr;

    vector<Point> wolnePola;
    for (int y = 0; y < plansza.getWysokosc(); ++y) {
        for (int x = 0; x < plansza.getSzerokosc(); ++x) {
            Point p(x, y);
            if (!waz.zajete(p)) {
                wolnePola.push_back(p);
            }
        }
    }

    if (wolnePola.empty()) {
        wygrana = true;
        koniecGry = true;
        return;
    }

    int szansa = rand() % 100;

    if (szansa < 20) {
        vector<Point> bezpiecznePola;
        Point head = waz.getHead();
        for (const auto& p : wolnePola) {
            int dystans = abs(p.getX() - head.getX()) + abs(p.getY() - head.getY());
            if (dystans > 3) {
                bezpiecznePola.push_back(p);
            }
        }

        if (!bezpiecznePola.empty()) {
            Point poz = bezpiecznePola[rand() % bezpiecznePola.size()];
            jedzenie = new toxicFood(poz, 10);
            return;
        }
    }

    Point poz = wolnePola[rand() % wolnePola.size()];
    if (szansa < 40) {
        jedzenie = new rareFood(poz);
    } else {
        jedzenie = new normalFood(poz);
    }
}

void Game::obsluzWejscie() {
    if (_kbhit()) {
        char klawisz = static_cast<char>(_getch());
        switch (klawisz) {
            case 'w': case 'W':
                waz.setKierunek(Kierunek::UP);
                break;
            case 's': case 'S':
                waz.setKierunek(Kierunek::DOWN);
                break;
            case 'a': case 'A':
                waz.setKierunek(Kierunek::LEFT);
                break;
            case 'd': case 'D':
                waz.setKierunek(Kierunek::RIGHT);
                break;
            case 'q': case 'Q':
                koniecGry = true;
                break;
            default:
                break;
        }
    }
}

void Game::aktualizuj() {
    waz.ruch();

    if (plansza.pozaBoard(waz.getHead()) || waz.selfKolizja()) {
        koniecGry = true;
        return;
    }

    if (jedzenie != nullptr && waz.getHead() == jedzenie->getPozycja()) {
        if (jedzenie->czyTrujace()) {
            koniecGry = true;
            return;
        }
        wynik += jedzenie->getPoints();
        waz.grow();
        generujJedzenie();
    } else if (jedzenie != nullptr) {
        jedzenie->update();
        if (jedzenie->czyWygaslo()) {
            generujJedzenie();
        }
    }
}

void Game::run() {
    while (!koniecGry) {
        cout << "\033[2J\033[H";
        if (jedzenie != nullptr) {
            plansza.tworzenie(wynik, waz.getHead(), waz.getBody(), *jedzenie);
        }
        obsluzWejscie();
        aktualizuj();
        this_thread::sleep_for(chrono::milliseconds(300));
    }

    cout << "\n============================\n";
    if (wygrana) {
        cout << "   WYGRANA! Pelna plansza!\n";
    } else {
        cout << "         KONIEC GRY!\n";
    }
    cout << "   Koncowy wynik: " << wynik << "\n";
    cout << "============================\n";
}