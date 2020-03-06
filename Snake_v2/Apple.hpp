#pragma once

#include <SFML/Graphics.hpp>
#include "SnakeBody.hpp"

using namespace sf;

class Apple : public CircleShape{
    public:
    int wspx, wspy;
    Apple(SnakeHead*);
    void setNewRandomPosition(SnakeHead*, SnakeBody*, int);
};