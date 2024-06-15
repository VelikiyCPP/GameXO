#pragma once
#ifndef AIPLAYER_HPP
#define AIPLAYER_HPP

#include "Board.hpp"
#include <utility>
#include <random>
#include <chrono>
#include <thread>

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

#endif // AIPLAYER_HPP