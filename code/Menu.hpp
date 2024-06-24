#pragma once

#include <vector>
#include "MenuItem.hpp"

class Menu {
public:
    Menu();
    void push_back(const MenuItem& item);
    void clear();
    void showAllMenu() const noexcept;
    MenuItem& operator[](const std::size_t i) noexcept;

private:
    std::vector<MenuItem> items_;
};