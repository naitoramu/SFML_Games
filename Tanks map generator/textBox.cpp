#include "textBox.hpp"

using namespace std;
using namespace sf;

TextBox::TextBox(){}

string TextBox::drawingTextBox(RenderWindow* window){
    if (event.type == sf::Event::TextEntered){
        user_input +=event.text.unicode;
        user_text.setString(user_input);
    }

    window->draw(user_text);

    if(event.type == Event::KeyPressed && event.key.code == Keyboard::Return){
        return user_input;
    }
}