#pragma once

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

#include "AssetManager.h"
#include "StateController.h"

enum AssetID
{
    MainFont = 0,
    Background,
    Food,
    Border,
    Snake,
};

struct Context
{
    std::unique_ptr<Engine::AssetManager> m_assets;
    std::unique_ptr<Engine::StateController> m_states;
    std::unique_ptr<sf::RenderWindow> m_window;

    Context()
    {
        m_assets = std::make_unique<Engine::AssetManager>();
        m_states = std::make_unique<Engine::StateController>();
        m_window = std::make_unique<sf::RenderWindow>();
    }
};

class Game
{
private:
    std::shared_ptr<Context> m_context;
    const sf::Time m_timePerFrame = sf::seconds(1.f / 60.f);

public:
    Game();
    ~Game();

    void Run();
};

