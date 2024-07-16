#pragma once

#include <cstddef>
#include <fstream>
#include <string>

class Setting {
public:
    Setting();

    void changeLanguage();
    std::string getLanguage()const noexcept;
    std::string getMode()const noexcept;

    std::size_t  getSelectLimit()const noexcept;

    char getSelectSymbolForAi();
    char& symbol();
    char& supportSelectSymbol();

    std::size_t& limitCount();
    std::size_t& boardSize();

    void         setNewLimit()noexcept;

    void loadRandomSelectSymbol()noexcept;
    void newMode()noexcept;

    

private:
    std::string language_;

    char selectSymbol_;
    char supportSelectSymbol_;

    std::size_t limitCount_;
    std::size_t selectLimit_;
    std::size_t boardSize_;

    std::string selectJsonText[2] {"classic_mode", "survival_mode"};
    short int   selectJsonTextCount;
};

//selectJsonText[selectJsonTextCount];