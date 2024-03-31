#include "headers/Snake.h"

Snake::Snake() : h_snake(std::list<sf::Sprite>(4))
{
    //set head to end of list and tail to beginning
    h_head = --h_snake.end();
    h_tail = h_snake.begin();
}

Snake::~Snake()
{
}

void Snake::Init(const sf::Texture &texture)
{
    //initialize the snake with 4 segments
    float x = 24.f;
    for (auto &segment : h_snake)
    {
        segment.setTexture(texture);
        segment.setPosition(x, 24.f);
        x += 24.f;
    }
}

void Snake::Move(const sf::Vector2f &direction)
{
    //move the snake by adding new segment to the head and removing the tail
    h_tail->setPosition(h_head->getPosition() + direction);
    h_head = h_tail;
    h_tail++;

    if (h_tail == h_snake.end())
    {
        h_tail = h_snake.begin();
    }
}

bool Snake::isOn(const sf::Sprite &other) const
{
    //check if the head is colliding with other sprite
    return other.getGlobalBounds().intersects(h_head->getGlobalBounds());
}

void Snake::Grow(const sf::Vector2f &direction)
{
    //add new segment to the snake
    sf::Sprite newSegment;
    newSegment.setTexture(*(h_snake.begin()->getTexture()));
    newSegment.setPosition(h_head->getPosition() + direction);
    h_head = h_snake.insert(h_head++, newSegment);
}

bool Snake::isColliding() const
{
    bool isColliding = false;

    //check if the head is colliding with any segment of the snake
    for (auto segment = h_snake.begin(); segment != h_snake.end(); segment++)
    {
        if (h_head != segment)
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
    for (auto &segment : h_snake)
    {
        target.draw(segment);
    }
}