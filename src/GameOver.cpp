#include "headers/GameOver.h"
#include "headers/GamePlay.h"

#include <SFML/Window/Event.hpp>

GameOver::GameOver(std::shared_ptr<Context> &context)
    : m_context(context),
      m_retrySelected(true),
      m_retryPressed(false),
      m_exitSelected(false),
      m_exitPressed(false)
{
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{
    //game title
    m_gameOver.setFont(m_context->m_assets->GetFont(FONT));
    m_gameOver.setString("Game Over");
    m_gameOver.setOrigin(m_gameOver.getLocalBounds().width / 2, m_gameOver.getLocalBounds().height / 2);
    m_gameOver.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 250.f);
    m_gameOver.setCharacterSize(50);

    //play
    m_retry.setFont(m_context->m_assets->GetFont(FONT));
    m_retry.setString("Retry");
    m_retry.setOrigin(m_retry.getLocalBounds().width / 2, m_retry.getLocalBounds().height / 2);
    m_retry.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 40.f);

    //exit
    m_exit.setFont(m_context->m_assets->GetFont(FONT));
    m_exit.setString("Exit");
    m_exit.setOrigin(m_exit.getLocalBounds().width / 2, m_exit.getLocalBounds().height / 2);
    m_exit.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 40.f);
}

void GameOver::ProcessInput()
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
                    if (!m_retrySelected)
                    {
                        m_retrySelected = true;
                        m_exitSelected = false;
                    }
                    break;
                }
                case sf::Keyboard::Down:
                {
                    if (!m_exitSelected)
                    {
                        m_retrySelected = false;
                        m_exitSelected = true;
                    }
                    break;
                }
                case sf::Keyboard::Return:
                {
                    m_exitPressed = false;
                    m_retryPressed = false;
                    if (m_retrySelected)
                    {
                        m_retryPressed = true;
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

void GameOver::Update(sf::Time deltaTime)
{
    if (m_retrySelected)
    {
        m_retry.setFillColor(sf::Color::Green);
        m_exit.setFillColor(sf::Color::White);
    }
    else
    {
        m_exit.setFillColor(sf::Color::Red);
        m_retry.setFillColor(sf::Color::White);
    }

    if (m_retryPressed)
    {
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
    }
    else if (m_exitPressed)
    {
        m_context->m_window->close();
    }

}

void GameOver::Draw()
{
    m_context->m_window->clear(sf::Color::Black);
    m_context->m_window->draw(m_gameOver);
    m_context->m_window->draw(m_retry);
    m_context->m_window->draw(m_exit);
    m_context->m_window->display();
}