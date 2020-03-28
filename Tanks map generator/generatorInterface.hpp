#include <SFML/Graphics.hpp>
#include <iostream>
#include "net.hpp"
#include "obstacle.hpp"
#include "saveFile.hpp"

using namespace sf;
using namespace std;

class GeneratorInterface{
    public:
    RenderWindow* window;
    Net net;
    Texture background_texture;
    Sprite background_sprite;
    Vector2i* mouse_position_relative_to_window = new Vector2i;
    Vector2f* mouse_position = new Vector2f;
    Vector2i* cell_position = new Vector2i;
    bool obstacles[18][32] = {0};
    int i_x, i_y;
    string map_name;
    Obstacle obstacle[18][32];
    int cellIsPressed();
    GeneratorInterface(RenderWindow*, Vector2f*, Vector2f*);
    bool display(bool*);
    void cellNumber();
    string drawingTextBox(Font* font);
    void mapReset();
};