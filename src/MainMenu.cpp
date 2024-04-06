#include "headers/MainMenu.h"
#include "headers/GamePlay.h"
#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<Context> &context)
    : h_context(context),
      h_playSelected(true),
      h_playPressed(false),
      h_exitSelected(false),
      h_exitPressed(false)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
    h_context->h_assets->AddFont(FONT, "assets/Baloo2.ttf");

    //game title
    h_gameTitle.setFont(h_context->h_assets->GetFont(FONT));
    h_gameTitle.setString("Snake");
    h_gameTitle.setOrigin(h_gameTitle.getLocalBounds().width / 2, h_gameTitle.getLocalBounds().height / 2);
    h_gameTitle.setPosition(h_context->h_window->getSize().x / 2 - 25.f, h_context->h_window->getSize().y / 2 - 250.f);
    h_gameTitle.setCharacterSize(50);

    //play button
    h_play.setFont(h_context->h_assets->GetFont(FONT));
    h_play.setString("Play");
    h_play.setOrigin(h_play.getLocalBounds().width / 2, h_play.getLocalBounds().height / 2);
    h_play.setPosition(h_context->h_window->getSize().x / 2, h_context->h_window->getSize().y / 2 - 40.f);

    //exit button
    h_exit.setFont(h_context->h_assets->GetFont(FONT));
    h_exit.setString("Exit");
    h_exit.setOrigin(h_exit.getLocalBounds().width / 2, h_exit.getLocalBounds().height / 2);
    h_exit.setPosition(h_context->h_window->getSize().x / 2, h_context->h_window->getSize().y / 2 + 40.f);
}

void MainMenu::ProcessInput()
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
                    if (!h_playSelected)
                    {
                        h_playSelected = true;
                        h_exitSelected = false;
                    }
                    break;
                }
                case sf::Keyboard::S:
                {
                    if (!h_exitSelected)
                    {
                        h_playSelected = false;
                        h_exitSelected = true;
                    }
                    break;
                }
                case sf::Keyboard::Return:
                {
                    h_exitPressed = false;
                    h_playPressed = false;
                    if (h_playSelected)
                    {
                        h_playPressed = true;
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

void MainMenu::Update(sf::Time deltaTime)
{
    if (h_playSelected)
    {
        h_play.setFillColor(sf::Color::Green);
        h_exit.setFillColor(sf::Color::White);
    }
    else
    {
        h_exit.setFillColor(sf::Color::Red);
        h_play.setFillColor(sf::Color::White);
    }

    if (h_playPressed)
    {
        h_context->h_states->Add(std::make_unique<GamePlay>(h_context), true);
    }
    else if (h_exitPressed)
    {
        h_context->h_window->close();
    }

}

void MainMenu::Draw()
{
    h_context->h_window->clear(sf::Color::Black);
    h_context->h_window->draw(h_gameTitle);
    h_context->h_window->draw(h_play);
    h_context->h_window->draw(h_exit);
    h_context->h_window->display();
}