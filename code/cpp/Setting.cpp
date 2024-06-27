#include <fstream>
#include <iostream>
#include <string>

#include "../hpp/Setting.hpp"

std::string getTextFromFile()noexcept {
    std::string text;

    std::ifstream file("Data/select_language.info");
    std::getline(file, text);

    return text;
}

Setting::Setting()
    : language_(getTextFromFile()), selectSymbol_('X'), limitMove_(10), boardSize_(3),
    cheatMode_(0), coin_(100), supportSelectSymbol_(selectSymbol_) {}

void Setting::changeLanguage() {
    std::string filePath = "Data/select_language.info";

    std::fstream file(filePath, std::ios::trunc | std::ios::in | std::ios::out);

    if (file.is_open()) {
        language_ == "en" ? language_ = "ru" : language_ = "en";

        file << language_;
        file.seekg(0);
        std::getline(file, language_);

        file.close();
        return;
    }

    throw std::runtime_error("Failed to open select language file");
}

std::string Setting::getLanguage()const noexcept {
    return language_;
}

char Setting::getSelectSymbolForAi() {
    return (selectSymbol_ == 'X' ? 'O' : 'X');
}

char& Setting::symbol() {
    return selectSymbol_;
}

char& Setting::supportSelectSymbol()
{
    return supportSelectSymbol_;
}

std::size_t& Setting::limitMove() {
    return limitMove_;
}

std::size_t& Setting::boardSize() {
    return boardSize_;
}

std::size_t& Setting::cheatMode() {
    return cheatMode_;
}

std::size_t& Setting::coin() {
    return coin_;
}

void Setting::loadRandomSelectSymbol()noexcept
{
    selectSymbol_ = (rand() % 2 == 0) ? 'O' : 'X';
}
