#include "game.h"
#include <iostream>
#include <stdexcept>


int main() {
    try {
        Game gra(20,15);
        gra.run();
    } catch (const exception& e) {
        std::cerr << "Blad krytyczny: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}