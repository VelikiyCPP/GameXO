#pragma once

#include <chrono>
#include <random>
#include <thread>
#include <utility>

#include "Board.hpp"

class AIPlayer {
public:
    AIPlayer(Board& board);
    std::pair<std::size_t, std::size_t> selectMoveAi(const int level = 1);
    void setLevel(const int level) noexcept;
    int getLevel() const noexcept;

private:
    std::pair<std::size_t, std::size_t> selectMoveRandomAi();
    Board* board_;
    int level_;
};