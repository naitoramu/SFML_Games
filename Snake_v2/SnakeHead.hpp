#pragma once

#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;

class SnakeBody;
class SnakeHead : public sf::RectangleShape{
    public:
	int size_x;
	int size_y;
	int x, y;
	int previous_z = (std::rand() % 4);
	int height, width;
	int height_p, width_p;
	int lim_l, lim_g, lim_r, lim_d;
	int a = 0;
	SnakeHead();
	SnakeHead(int, int, int, int, int, int, int);
    void granice();
	void sterowanie(int);
	void newPosition();
	void move();
	bool kolizja(SnakeBody*, int);
};