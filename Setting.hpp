#pragma once
#ifndef SETTING_HPP
#define SETTING_HPP

#include <iostream>

class Setting {
public:
    Setting();

    void changeLanguage() noexcept;
    std::string getLanguage();

    char getSelectSymbolForAi() const;
    char& symbol();

    std::size_t& limitMove();
    std::size_t& boardSize();
    std::size_t& cheatMode();
    std::size_t& coin();

private:
    std::string language_;
    char selectSymbol_;
    std::size_t limitMove_;
    std::size_t boardSize_;
    std::size_t cheatMode_;
    std::size_t coin_;
};

#endif // SETTING_HPP