#pragma once

#include <iostream>
#include <string>

class MenuItem {
public:
    MenuItem(const std::string& text, const std::size_t dopValue = 0);
    MenuItem(const std::string& text, const std::string& dopText);

    std::string getText() const;
    std::string getTextTwo() const noexcept;
    std::size_t getValue() const noexcept;

    void setTextTwo(const std::string& newText) noexcept;
    void setValue(const std::size_t newValue) noexcept;

    void showStatistic() const noexcept;

private:
    const std::string text_;

    std::size_t value_;
    std::string textTwo_;
};