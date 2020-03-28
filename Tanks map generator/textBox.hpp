#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class TextBox : public Text{
    public:
    Text user_text;
    String user_input;
    Event event;
    TextBox();
    string drawingTextBox(RenderWindow*);
};
