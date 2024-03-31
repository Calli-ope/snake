#pragma once

#include <memory>
#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "Game.h"

class MainMenu : public Engine::State
{
private:
    std::shared_ptr<Context> h_context;
    sf::Text h_gameTitle;
    sf::Text h_play;
    sf::Text h_exit;

    bool h_playSelected;
    bool h_playPressed;
    bool h_exitSelected;
    bool h_exitPressed;

public:
    MainMenu(std::shared_ptr<Context>& context);
    ~MainMenu();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
};
