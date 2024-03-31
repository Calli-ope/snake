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
    std::shared_ptr<Context> h_context;
    sf::Sprite h_background;
    sf::Sprite h_food;
    std::array<sf::Sprite, 4> h_border;

    Snake h_snake;
    sf::Vector2f h_direction;
    sf::Time h_elapsedTime;

    sf::Text h_scoreLabel;
    int h_score;

public:
    GamePlay(std::shared_ptr<Context>& context);
    ~GamePlay();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
};
