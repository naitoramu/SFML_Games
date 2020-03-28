#include <SFML/Graphics.hpp>
#include "button.hpp"
#include <iostream>

using namespace std;
using namespace sf;

class Menu{
    public:
    Button* button;
    RenderWindow* window;
    int buttons_count;
    Texture backgroung_texture;
    Sprite background_sprite;
    Menu(RenderWindow*, int, int, int, int);
    bool display(int*);
};