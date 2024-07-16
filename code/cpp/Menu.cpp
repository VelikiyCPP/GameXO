#include <iostream>

#include "../hpp/Menu.hpp"

Menu::Menu() {}

void Menu::push_back(const MenuItem& item) {
    items_.push_back(item);
}

void Menu::clear() {
    items_.clear();
}

void Menu::showAllMenu() const noexcept {
    std::cout << "          /\\         \n";
    std::cout << "         /__\\        \n";
    std::cout << "        /____\\       \n";
    std::cout << "        | [] |        \n";
    std::cout << "        |____|        \n";
    std::cout << "________#||||#___________\n";
    for (const auto& element : items_) {
        element.showStatistic();
    }
    std::cout << "--------------------" << std::endl;
}

MenuItem& Menu::operator[](const std::size_t i) noexcept {
    return items_[i];
}