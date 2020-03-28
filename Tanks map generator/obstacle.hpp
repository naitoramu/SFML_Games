#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Obstacle : public Sprite{
    public:
    Texture tekstura;
    Vector2f* position = new Vector2f;
    Vector2f* origin = new Vector2f;
    Obstacle();
};