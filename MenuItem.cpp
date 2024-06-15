#include "MenuItem.hpp"

MenuItem::MenuItem(const std::string& text, const std::size_t value, std::size_t* dopValue, const std::string dopText)
    : text_(text), value_(value), dopValue_(dopValue), dopText_(dopText) {}

std::string MenuItem::getText() const {
    return text_;
}

std::size_t MenuItem::getValue() const {
    return value_;
}

void MenuItem::showStatistic() const noexcept {
    if (value_ != 0) {
        if (dopValue_ != nullptr || dopText_ != "\0") {
            std::cout << value_ << ". " << text_
                << (dopText_ != "\0" ? dopText_ : std::to_string(*dopValue_))
                << '\n';
        }
        else {
            std::cout << value_ << ". " << text_ << '\n';
        }
    }
    else if (dopValue_ != nullptr) {
        std::cout << text_
            << (dopText_ != "\0" ? dopText_ : std::to_string(*dopValue_))
            << '\n';
    }
    else {
        std::cout << text_ << '\n';
    }
}

void MenuItem::setDopText(const char dopChar) noexcept {
    dopText_ = dopChar;
}

void MenuItem::setDopText(const std::string dopText) noexcept {
    dopText_ = dopText;
}