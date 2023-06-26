#pragma once

#include "Screen.h"

class ErrorScreen : public Screen
{
public:

    explicit ErrorScreen(const std::string &errorMessage);
    explicit ErrorScreen(std::string &&errorMessage);

    ~ErrorScreen() override = default;

    std::unique_ptr<Screen> run(sf::RenderWindow &window) override;


private:
    std::string m_errorMessage;

};