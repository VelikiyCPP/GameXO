#include <iostream>
#include <exception>

#include "../hpp/Game.hpp"

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