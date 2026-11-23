# Snake (C++20)

Konsolowa implementacja klasycznej gry **Snake** napisana w języku **C++20** z wykorzystaniem paradygmatów programowania obiektowego (enkapsulacja, dziedziczenie, polimorfizm, kompozycja, przeciążanie operatorów oraz dynamiczne zarządzanie pamięcią).

---

## Zasady gry i mechaniki

* **Sterowanie w czasie rzeczywistym:** Wąż porusza się płynnie po planszy o wymiarach $20 \times 15$, a gracz zmienia jego kierunek bez konieczności zatwierdzania klawiszem Enter (`W/A/S/D`, wyjście: `Q`).
* **System jedzenia (polimorficzny):** Na planszy pojawia się losowo jeden z trzech typów obiektów dziedziczących po klasie abstrakcyjnej `Food`:

| Typ obiektu | Symbol | Punkty | Szansa pojawienia | Dodatkowe właściwości |
| :--- | :---: | :---: | :---: | :--- |
| **`normalFood`** | `*` | `+1` | 60% | Standardowe pożywienie wydłużające węża o 1 segment. |
| **`rareFood`** | `$` | `+5` | 20% | Rzadki bonus punktowy. |
| **`toxicFood`** | `*` / `X` | `0` | 20% | Zjedzenie kończy grę. Z daleka (dystans Manhattan $> 3$) maskuje się jako `*`, z bliska ($\le 3$) ujawnia symbol `X`. Wygasa automatycznie po **10 ruchach** węża i pojawia się wyłącznie w bezpiecznej odległości ($> 3$) od głowy. |

* **Warunki zakończenia gry:**
    * **Przegrana:** uderzenie w ścianę planszy, kolizja z własnym ogonem lub zjedzenie `toxicFood`.
    * **Wygrana:** zapełnienie wszystkich wolnych pól na planszy.

---

## Architektura klas i założenia obiektowe

* **`Point` (`Point.h`, `Point.cpp`):** Reprezentuje współrzędne `(x, y)` na planszy. Zapewnia enkapsulację pól oraz przeciążone operatory `==`, `!=` i strumieniowy `<<`.
* **`Board` (`Board.h`, `Board.cpp`):** Odpowiada za wymiary planszy, sprawdzanie wyjścia poza granice (`pozaBoard`) oraz renderowanie stanu gry w konsoli (`tworzenie`).
* **`Snake` (`Snake.h`, `Snake.cpp`):** Zarządza pozycją głowy, segmentami ciała (`std::vector<Point>`), kierunkiem ruchu (`enum class Kierunek`), wzrostem oraz wykrywaniem autokolizji (`selfKolizja`) i zajętości pól (`zajete`).
* **`Food` (`Food.h`, `Food.cpp`):** Abstrakcyjna klasa bazowa z wirtualnym destruktorem (`virtual ~Food()`), metodami czysto wirtualnymi (`getSymbol`, `getPoints`) oraz wirtualnymi (`czyTrujace`, `update`, `czyWygaslo`).
* **`normalFood`, `rareFood`, `toxicFood` (`FoodType.h`, `FoodType.cpp`):** Klasy pochodne przesłaniające zachowanie klasy bazowej z użyciem `override`.
* **`Game` (`game.h`, `game.cpp`):** Główny kontroler łączący wszystkie komponenty (kompozycja). Zarządza pętlą gry, obsługą wejścia, losowaniem jedzenia z zabezpieczeniem przed nieskończoną pętlą oraz zwalnianiem pamięci dynamicznej (`Food*`).

---

## Diagram klas UML

```mermaid
classDiagram
    class Point {
        -int x
        -int y
        +Point(int x, int y)
        +getX() int
        +getY() int
        +setX(int x) void
        +setY(int y) void
        +operator==(Point other) bool
        +operator!=(Point other) bool
    }

    class Board {
        -int szerokosc
        -int wysokosc
        +Board(int s1, int w1)
        +getSzerokosc() int
        +getWysokosc() int
        +pozaBoard(Point p) bool
        +tworzenie(int wynik, Point head, vector~Point~ body, Food food) void
    }

    class Snake {
        -Point head
        -vector~Point~ body
        -Kierunek chwilowyKierunek
        -bool shouldGrow
        +Snake(Point start, int startDlugosc)
        +setKierunek(Kierunek newKierunek) void
        +ruch() void
        +grow() void
        +getHead() Point
        +getBody() vector~Point~
        +selfKolizja() bool
        +zajete(Point p) bool
    }

    class Food {
        <<abstract>>
        #Point pozycja
        +Food(Point poz)
        +~Food()
        +getPosition() Point
        +getSymbol(Point snakeHead)* char
        +getPoints()* int
        +czyTrujace() bool
        +update() void
        +czyWygaslo() bool
    }

    class normalFood {
        +normalFood(Point poz)
        +getSymbol(Point snakeHead) char
        +getPoints() int
    }

    class rareFood {
        +rareFood(Point poz)
        +getSymbol(Point snakeHead) char
        +getPoints() int
    }

    class toxicFood {
        -int movesLeft
        +toxicFood(Point poz, int duration)
        +getSymbol(Point snakeHead) char
        +getPoints() int
        +czyTrujace() bool
        +update() void
        +czyWygaslo() bool
    }

    class Game {
        -Board plansza
        -Snake waz
        -Food* jedzenie
        -int wynik
        -bool koniecGry
        -bool wygrana
        -generujJedzenie() void
        -obsluzWejscie() void
        -aktualizuj() void
        +Game(int szerokosc, int wysokosc)
        +~Game()
        +uruchom() void
    }

    Food <|-- normalFood
    Food <|-- rareFood
    Food <|-- toxicFood
    Game *-- Board
    Game *-- Snake
    Game *-- Food
    Snake *-- Point
    Food *-- Point
    Board ..> Food
    Board ..> Point