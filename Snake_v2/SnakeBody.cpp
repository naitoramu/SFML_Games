#include "SnakeBody.hpp"

using namespace sf;

SnakeBody::SnakeBody(){}

void SnakeBody::move(SnakeHead *previous){
    setPosition(previous->getPosition());
}

void SnakeBody::move(SnakeBody *previous){
    setPosition(previous->getPosition());
}

void SnakeBody::konstruktor(SnakeHead *previous, int wspx, int wspy){
    size_x = previous->size_x;
    size_y = previous->size_y;
    x = wspx;
    y = wspy;
    setSize(sf::Vector2f(size_x, size_y));
    setOrigin(size_x / 2, size_y / 2);
    setFillColor(sf::Color(35, 45, 20));
    setPosition(x, y);
}