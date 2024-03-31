#pragma once

#include <memory>
#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "Game.h"

class GameOver : public Engine::State
{
private:
    std::shared_ptr<Context> h_context;
    sf::Text h_gameOver;
    sf::Text h_retry;
    sf::Text h_exit;

    bool h_retrySelected;
    bool h_retryPressed;
    bool h_exitSelected;
    bool h_exitPressed;

public:
    GameOver(std::shared_ptr<Context>& context);
    ~GameOver();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
};
