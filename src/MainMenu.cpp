#include "headers/MainMenu.h"
#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<Context> &context)
    : m_context(context),
      m_playSelected(true),
      m_playPressed(false),
      m_exitSelected(false),
      m_exitPressed(false)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
    m_context->m_assets->AddFont(MainFont, "assets/Baloo2.ttf");

    //game title
    m_gameTitle.setFont(m_context->m_assets->GetFont(MainFont));
    m_gameTitle.setString("Snake");
    m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2, m_gameTitle.getLocalBounds().height / 2);
    m_gameTitle.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 150.f);

    //play
    m_play.setFont(m_context->m_assets->GetFont(MainFont));
    m_play.setString("Play");
    m_play.setOrigin(m_play.getLocalBounds().width / 2, m_play.getLocalBounds().height / 2);
    m_play.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 25.f);
    m_play.setCharacterSize(20);

    //exit
    m_exit.setFont(m_context->m_assets->GetFont(MainFont));
    m_exit.setString("Exit");
    m_exit.setOrigin(m_exit.getLocalBounds().width / 2, m_exit.getLocalBounds().height / 2);
    m_exit.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 25.f);
    m_exit.setCharacterSize(20);
}

void MainMenu::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::Up:
                {
                    if (!m_playSelected)
                    {
                        m_playSelected = true;
                        m_exitSelected = false;
                    }
                    break;
                }
                case sf::Keyboard::Down:
                {
                    if (!m_exitSelected)
                    {
                        m_playSelected = false;
                        m_exitSelected = true;
                    }
                    break;
                }
                case sf::Keyboard::Return:
                {
                    m_exitPressed = false;
                    m_playPressed = false;
                    if (m_playSelected)
                    {
                        m_playPressed = true;
                    }
                    else
                    {
                        m_exitPressed = true;
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
    if (m_playSelected)
    {
        m_play.setFillColor(sf::Color::Green);
        m_exit.setFillColor(sf::Color::White);
    }
    else
    {
        m_exit.setFillColor(sf::Color::Red);
        m_play.setFillColor(sf::Color::White);
    }

    if (m_playPressed)
    {

    }
    else if (m_exitPressed)
    {
        m_context->m_window->close();
    }

}

void MainMenu::Draw()
{
    m_context->m_window->clear(sf::Color::Black);
    m_context->m_window->draw(m_gameTitle);
    m_context->m_window->draw(m_play);
    m_context->m_window->draw(m_exit);
    m_context->m_window->display();
}