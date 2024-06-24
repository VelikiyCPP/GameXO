#pragma once

#include <array>
#include <cstddef>

class Board {
public:
    Board();

    bool makeMove(const std::size_t row, const std::size_t col, const char symbol) noexcept;

    void printBoard() const noexcept;
    void resetBoard() noexcept;
    void minusAllHealthByte(const char byte) noexcept;
    void removeCurrentSymbol(const char byte) noexcept;

    [[nodiscard]] bool isWinner(const char symbol) noexcept;
    [[nodiscard]] bool isValidMove(const std::size_t row, const std::size_t col) noexcept;
    [[nodiscard]] bool isFree(const std::size_t y, const std::size_t x) const noexcept;

private:
    struct HealthByte {
        int health_ = 4;
        char byte_ = ' ';
    };

    std::array<std::array<HealthByte, 3>, 3> board_;

    enum class Winners : std::size_t { OVICTORY, XVICTORY, TIE }; // TODO: TIE - реализовать (стандартные крестики нолик) (setting/board)
    static constexpr std::size_t boardSize_ = 3;
};