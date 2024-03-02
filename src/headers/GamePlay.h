#pragma once

#include <memory>
#include <array>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "Game.h"
#include "Snake.h"

class GamePlay : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    sf::Sprite m_background;
    sf::Sprite m_food;
    std::array<sf::Sprite, 4> m_border;

    Snake m_snake;
    sf::Vector2f m_direction;
    sf::Time m_elapsedTime;

    sf::Text m_scoreLabel;
    int m_score;

public:
    GamePlay(std::shared_ptr<Context>& context);
    ~GamePlay();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
    void Pause() override;
    void Start() override;
};
