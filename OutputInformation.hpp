#pragma once
#ifndef OUTPUTINFORMATION_HPP
#define OUTPUTINFORMATION_HPP

#include <thread>
#include <iostream>
#include <nlohmann/json.hpp>

namespace OI
{
    enum class typeMessage : std::size_t {
        ERROR,
        INFO,
        WARNING,
        SUCCESS,
        DEBUG,
        SYSTEM,
        UNKNOWN
    };

    class OutputInformation {
    public:
        OutputInformation() {}

        void messageFromGame(const typeMessage messageType,
            const std::string& message,
            const std::time_t time = 0) const noexcept;

        void messageFromGame(const nlohmann::json& messageJson) const noexcept;
    };
}


#endif // DEBUGCLASS_HPP