#pragma once

#include <ctime>
#include <string>

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

    void loadMessages(const std::string& language);
    void messageJson(const std::string& key, const std::time_t time, const typeMessage type = typeMessage::UNKNOWN)noexcept;
    void setLanguage(const std::string& newLanguage)noexcept;
    std::string getTextFromJson(const std::string& key);
private:
    nlohmann::json messages_;
    std::string    language_;
};
