#pragma once
#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include "MenuItem.hpp"

namespace VisualMenu {
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
} // namespace VisualMenu

#endif // MENU_HPP