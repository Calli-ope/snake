#include "headers/Game.h"
#include "headers/MainMenu.h"

Game::Game() : h_context(std::make_shared<Context>())
{
    h_context->h_window->create(sf::VideoMode(960, 528), "Snake", sf::Style::Close);
    h_context->h_states->Add(std::make_unique<MainMenu>(h_context));
}

Game::~Game()
{
}

void Game::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (h_context->h_window->isOpen())
    {
        timeSinceLastUpdate += clock.restart();

        while (timeSinceLastUpdate > h_timePerFrame)
        {
            timeSinceLastUpdate -= h_timePerFrame;

            h_context->h_states->ProcessStateChanges();
            h_context->h_states->GetCurrent()->ProcessInput();
            h_context->h_states->GetCurrent()->Update(h_timePerFrame);
            h_context->h_states->GetCurrent()->Draw();
        }
    }
}
