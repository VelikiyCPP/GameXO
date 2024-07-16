#pragma once

#include <vector>
#include <cstddef>

class Board {
public:
    inline static std::size_t boardSize_ = 3;
    constexpr static std::size_t boardSizeMax_ = 5;

    Board();

    bool makeMove(const std::size_t row, const std::size_t col, const char symbol) noexcept;

    void printBoard() const noexcept;
    void resetBoard() noexcept;
    void minusAllHealthByte(const char byte) noexcept;
    void removeCurrentSymbol(const char byte) noexcept;
    std::size_t incrementNewSize()noexcept;


    [[nodiscard]] char getCell(const int x, const int y)const noexcept;
    [[nodiscard]] std::size_t getSizeMap()const noexcept;
    [[nodiscard]] bool        isWinner(const char symbol, const std::size_t levelAI) noexcept;
    [[nodiscard]] bool        isTie()noexcept;
    [[nodiscard]] bool        isValidMove(const std::size_t row, const std::size_t col) noexcept;
    [[nodiscard]] bool        isFree(const std::size_t y, const std::size_t x) const noexcept;

    void undoMove(const int x, const int y)noexcept;

private:
    struct HealthByte {
        HealthByte() = default;
        HealthByte(int health, char byte) : health_(health), byte_(byte) {}

        int health_ = boardSize_ + 1;
        char byte_ = ' ';
    };

    std::vector<std::vector<HealthByte>> board_;

    enum class Winners : std::size_t { OVICTORY, XVICTORY, TIE };
};