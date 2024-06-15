#pragma once
#ifndef MENUITEM_HPP
#define MENUITEM_HPP

#include <iostream>
#include <string>

class MenuItem {
public:
    MenuItem(const std::string& text, const std::size_t value = 0, std::size_t* dopValue = nullptr, const std::string dopText = "\0");
    std::string getText() const;
    std::size_t getValue() const;
    void showStatistic() const noexcept;
    void setDopText(const char dopChar = '\0') noexcept;
    void setDopText(const std::string dopText = "\0") noexcept;

private:
    const std::string text_;
    const std::size_t value_;
    std::size_t* dopValue_;
    std::string dopText_;
};

#endif // MENUITEM_HPP