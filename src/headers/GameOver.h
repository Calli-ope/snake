#pragma once

#include <memory>
#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "Game.h"

class GameOver : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    sf::Text m_gameOver;
    sf::Text m_retry;
    sf::Text m_exit;

    bool m_retrySelected;
    bool m_retryPressed;
    bool m_exitSelected;
    bool m_exitPressed;

public:
    GameOver(std::shared_ptr<Context>& context);
    ~GameOver();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
};
