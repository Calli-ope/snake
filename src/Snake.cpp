#include "headers/Snake.h"

Snake::Snake() : m_snake(std::list<sf::Sprite>(4))
{
    m_head = --m_snake.end();
    m_tail = m_snake.begin();
}

Snake::~Snake()
{
}

void Snake::Init(const sf::Texture &texture)
{
    float x = 24.f;
    for (auto &segment : m_snake)
    {
        segment.setTexture(texture);
        segment.setPosition(x, 24.f);
        x += 24.f;
    }
}

void Snake::Move(const sf::Vector2f &direction)
{
    m_tail->setPosition(m_head->getPosition() + direction);
    m_head = m_tail;
    m_tail++;

    if (m_tail == m_snake.end())
    {
        m_tail = m_snake.begin();
    }
}

bool Snake::isOn(const sf::Sprite &other) const
{
    return other.getGlobalBounds().intersects(m_head->getGlobalBounds());
}

void Snake::Grow(const sf::Vector2f &direction)
{
    sf::Sprite newSegment;
    newSegment.setTexture(*(m_snake.begin()->getTexture()));
    newSegment.setPosition(m_head->getPosition() + direction);
    m_head = m_snake.insert(m_head++, newSegment);
}

bool Snake::isColliding() const
{
    bool isColliding = false;

    for (auto segment = m_snake.begin(); segment != m_snake.end(); segment++)
    {
        if (m_head != segment)
        {
            isColliding = isOn(*segment);
            if (isColliding)
            {
                break;
            }
        }
    }
    return isColliding;
}


void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto &segment : m_snake)
    {
        target.draw(segment);
    }
}