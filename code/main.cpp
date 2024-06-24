#include "Game.hpp"

#include <iostream>
#include <exception>

int main()
{
    try {
        Game game;
        game.start();
    }
    catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
    }
    catch (...) {
        std::cerr << "Code throw error\n";
        return 1;
    }
    return 0;
}