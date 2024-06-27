#include "../hpp/MenuItem.hpp"

MenuItem::MenuItem(const std::string& text, const std::size_t value)
    : text_(text), value_(value), textTwo_("") {}

MenuItem::MenuItem(const std::string& text, const std::string& textTwo)
    : text_(text), textTwo_(textTwo), value_(0) {}

std::string MenuItem::getText() const {
    return text_;
}

void MenuItem::showStatistic() const noexcept {
    std::cout << text_;

    if (textTwo_ != "") {
        std::cout << textTwo_;
    }
    else if (value_ != 0) {
        std::cout << value_;
    }
    else {
        std::cout << "";
    }

    std::cout << std::endl;
}

std::string MenuItem::getTextTwo() const noexcept {
    return textTwo_;
}

std::size_t MenuItem::getValue() const noexcept {
    if (value_ != 0) {
        return value_;
    }
    return 0;
}

void MenuItem::setTextTwo(const std::string& newText) noexcept
{
    textTwo_ = newText;
}

void MenuItem::setValue(const std::size_t newValue) noexcept
{
    value_ = newValue;
}
