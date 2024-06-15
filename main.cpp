#include "Game.hpp"

int main()
{
    try {
        GameXO::Game game;
        game.start();
    }
    catch (...) {
        std::cerr << "Code throw error\n";
        return 1;
    }
    return 0;
}