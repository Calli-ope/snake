#include <SFML/Graphics/CircleShape.hpp>

#include "headers/Game.h"
#include "headers/MainMenu.h"

Game::Game() : m_context(std::make_shared<Context>())
{
    m_context->m_window->create(sf::VideoMode(640,360), "Snake", sf::Style::Close);
    m_context->m_states->Add(std::make_unique<MainMenu>(m_context));
}

Game::~Game()
{
}

void Game::Run()
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (m_context->m_window->isOpen())
    {
        timeSinceLastUpdate += clock.restart();

        while (timeSinceLastUpdate > m_timePerFrame)
        {
            timeSinceLastUpdate -= m_timePerFrame;

            m_context->m_states->ProcessStateChanges();
            m_context->m_states->GetCurrent()->ProcessInput();
            m_context->m_states->GetCurrent()->Update(m_timePerFrame);
            m_context->m_states->GetCurrent()->Draw();
        }
    }
}
