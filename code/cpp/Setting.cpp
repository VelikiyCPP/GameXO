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
    : language_(getTextFromFile()), selectSymbol_('X'), selectLimit_(999), limitCount_(selectLimit_), boardSize_(3),
                                    supportSelectSymbol_(selectSymbol_), selectJsonTextCount(0) {}

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

std::string Setting::getMode()const noexcept {
    return selectJsonText[selectJsonTextCount];
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

std::size_t& Setting::limitCount() {
    return limitCount_;
}

std::size_t& Setting::boardSize() {
    return boardSize_;
}



void Setting::setNewLimit()noexcept {
    switch (selectLimit_)
    {
    case 5:
        selectLimit_ = 10;
        break;
    case 10:
        selectLimit_ = 20;
        break;
    case 20:
        selectLimit_ = 25;
        break;
    case 25:
        selectLimit_ = 999;
        break;
    case 999:
        selectLimit_ = 5;
        break;
    default:
        break;
    }
}

void Setting::newMode()noexcept {
    if(selectJsonTextCount++ == 1){
        selectJsonTextCount = 0;
    }
}

void Setting::loadRandomSelectSymbol()noexcept
{
    selectSymbol_ = (rand() % 2 == 0) ? 'O' : 'X';
}

std::size_t Setting::getSelectLimit()const noexcept {
    return selectLimit_;
}