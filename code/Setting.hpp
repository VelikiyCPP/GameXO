#pragma once

#include <cstddef>
#include <fstream>
#include <string>

class Setting {
public:
    Setting();

    void changeLanguage();
    std::string getLanguage()const noexcept;

    char getSelectSymbolForAi();
    char& symbol();
    char& supportSelectSymbol();

    std::size_t& limitMove();
    std::size_t& boardSize();
    std::size_t& cheatMode();
    std::size_t& coin();

    void loadRandomSelectSymbol()noexcept;

private:
    std::string language_;

    char selectSymbol_;
    char supportSelectSymbol_;

    std::size_t limitMove_;
    std::size_t boardSize_;
    std::size_t cheatMode_;
    std::size_t coin_;
};