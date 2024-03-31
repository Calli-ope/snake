#pragma once

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

#include "AssetManager.h"
#include "StateController.h"

enum AssetID
{
    FONT = 0,
    BACKGROUND,
    FOOD,
    BORDER,
    SNAKE,
};

struct Context
{
    std::unique_ptr<Engine::AssetManager> h_assets;
    std::unique_ptr<Engine::StateController> h_states;
    std::unique_ptr<sf::RenderWindow> h_window;

    Context()
    {
        h_assets = std::make_unique<Engine::AssetManager>();
        h_states = std::make_unique<Engine::StateController>();
        h_window = std::make_unique<sf::RenderWindow>();
    }
};

class Game
{
private:
    std::shared_ptr<Context> h_context;
    const sf::Time h_timePerFrame = sf::seconds(1.f / 60.f);

public:
    Game();
    ~Game();

    void Run();
};

