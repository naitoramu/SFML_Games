#pragma once

#include <SFML/Graphics.hpp>
#include <ctime>
#include "SnakeHead.hpp"

using namespace sf;

class SnakeBody : public SnakeHead{
    public:
	SnakeBody();
	void move(SnakeHead*);
	void move(SnakeBody*);
	void konstruktor(SnakeHead*, int, int);
};