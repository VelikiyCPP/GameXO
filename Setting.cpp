#include "Setting.hpp"


Setting::Setting()
    : language_("en"), selectSymbol_('X'), limitMove_(10), boardSize_(3),
    cheatMode_(0), coin_(100) {}

void Setting::changeLanguage() noexcept {
    language_ == "en" ? language_ = "ru" : language_ = "en";
}

std::string Setting::getLanguage() {
    return language_;
}

char Setting::getSelectSymbolForAi() const {
    if (selectSymbol_ == 'R') {
        std::srand(static_cast<unsigned int>(std::time(0)));
        return std::rand() % 2 == 0 ? 'X' : 'O';
    }
    return (selectSymbol_ == 'X' ? 'O' : 'X');
}

char& Setting::symbol() {
    return selectSymbol_;
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