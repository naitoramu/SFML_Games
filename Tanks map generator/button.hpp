#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Button : public Sprite{
    public:
    Texture tekstura;
    Vector2f* position = new Vector2f;
    Vector2f* button_size = new Vector2f;
    Vector2i* mouse_position_relative_to_window = new Vector2i;
    Vector2f* mouse_position = new Vector2f;
    Button();
    Button(int, int, string);
    void konstruktor(int, int, string);
    bool isPressed(RenderWindow*);
};