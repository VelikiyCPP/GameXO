#pragma once

#include <array>
#include <cstddef>

class Board {
public:
    Board();
    void printBoard() const noexcept;
    bool isValidMove(const std::size_t row, const std::size_t col) noexcept;
    bool makeMove(const std::size_t row, const std::size_t col, const char symbol) noexcept;
    bool isFree(const std::size_t y, const std::size_t x) const noexcept;
    bool isWinner(const char symbol) noexcept;
    void clearBoard();
    void minusAllHealthByte(const char byte) noexcept;

private:
    struct HealthByte {
        int health_ = 4;
        char byte_ = ' ';
    };

    std::array<std::array<HealthByte, 3>, 3> board_;

    enum class Winners : std::size_t { OVICTORY, XVICTORY, TIE };
    static constexpr std::size_t boardSize_ = 3;
};