#include "Apple.hpp"

using namespace sf;

Apple::Apple(SnakeHead *head)
{
    bool b = true;
    while (b)
    {
        wspx = (((std::rand() % 15) + 1) * head->size_x) + 320;
        wspy = (((std::rand() % 15) + 1) * head->size_y) + 40;
        if (wspy != head->getPosition().y || wspx != head->getPosition().x)
            b = false;
    }
    setRadius(20);
    setOrigin(sf::Vector2f(20, 20));
    setFillColor(Color(180, 5 ,20));
    setPosition(wspx, wspy);
}

void Apple::setNewRandomPosition(SnakeHead *head, SnakeBody *body, int segmenty){
    bool b = true;
    while (b){
        wspx = (((std::rand() % 15) + 1) * head->size_x) + 320;
        wspy = (((std::rand() % 15) + 1) * head->size_y) + 40;
        int i = 0;
        for (; i <= segmenty; i++){
            if (i == 0 && head->getPosition().x == wspx && head->getPosition().y == wspy)
                break;
            else if (i != 0 && body[i - 1].getPosition().x == wspx && body[i - 1].getPosition().y == wspy)
                break;
        }
        if (i - 1 == segmenty)
            b = false;
    }
    setPosition(wspx, wspy);
}