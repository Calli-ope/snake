#include "headers/GameOver.h"
#include "headers/GamePlay.h"

#include <SFML/Window/Event.hpp>

GameOver::GameOver(std::shared_ptr<Context> &context)
    : h_context(context),
      h_retrySelected(true),
      h_retryPressed(false),
      h_exitSelected(false),
      h_exitPressed(false)
{
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{
    //game title
    h_gameOver.setFont(h_context->h_assets->GetFont(FONT));
    h_gameOver.setString("Game Over");
    h_gameOver.setOrigin(h_gameOver.getLocalBounds().width / 2, h_gameOver.getLocalBounds().height / 2);
    h_gameOver.setPosition(h_context->h_window->getSize().x / 2 - 45.f, h_context->h_window->getSize().y / 2 - 250.f);
    h_gameOver.setCharacterSize(50);

    //play button
    h_retry.setFont(h_context->h_assets->GetFont(FONT));
    h_retry.setString("Retry");
    h_retry.setOrigin(h_retry.getLocalBounds().width / 2, h_retry.getLocalBounds().height / 2);
    h_retry.setPosition(h_context->h_window->getSize().x / 2, h_context->h_window->getSize().y / 2 - 40.f);

    //exit button
    h_exit.setFont(h_context->h_assets->GetFont(FONT));
    h_exit.setString("Exit");
    h_exit.setOrigin(h_exit.getLocalBounds().width / 2, h_exit.getLocalBounds().height / 2);
    h_exit.setPosition(h_context->h_window->getSize().x / 2, h_context->h_window->getSize().y / 2 + 40.f);
}

void GameOver::ProcessInput()
{
    sf::Event event;
    while (h_context->h_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            h_context->h_window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::W:
                {
                    if (!h_retrySelected)
                    {
                        h_retrySelected = true;
                        h_exitSelected = false;
                    }
                    break;
                }
                case sf::Keyboard::S:
                {
                    if (!h_exitSelected)
                    {
                        h_retrySelected = false;
                        h_exitSelected = true;
                    }
                    break;
                }
                case sf::Keyboard::Return:
                {
                    h_exitPressed = false;
                    h_retryPressed = false;
                    if (h_retrySelected)
                    {
                        h_retryPressed = true;
                    }
                    else
                    {
                        h_exitPressed = true;
                    }
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }
}

void GameOver::Update(sf::Time deltaTime)
{
    if (h_retrySelected)
    {
        h_retry.setFillColor(sf::Color::Green);
        h_exit.setFillColor(sf::Color::White);
    }
    else
    {
        h_exit.setFillColor(sf::Color::Red);
        h_retry.setFillColor(sf::Color::White);
    }

    if (h_retryPressed)
    {
        h_context->h_states->Add(std::make_unique<GamePlay>(h_context), true);
    }
    else if (h_exitPressed)
    {
        h_context->h_window->close();
    }

}

void GameOver::Draw()
{
    h_context->h_window->clear(sf::Color::Black);
    h_context->h_window->draw(h_gameOver);
    h_context->h_window->draw(h_retry);
    h_context->h_window->draw(h_exit);
    h_context->h_window->display();
}