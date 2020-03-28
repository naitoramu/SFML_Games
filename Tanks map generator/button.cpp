#include "button.hpp"
#include <iostream>

using namespace std;
using namespace sf;

Button::Button(int x, int y, string name){
    position->x = x;
    position->y = y;
    if(!tekstura.loadFromFile("img/" + name + ".png")){
        cout << "Cannot load " << name << endl;
    }else{
        tekstura.loadFromFile("img/" + name + ".png");
    }
    setTexture(tekstura);
    button_size->x = tekstura.getSize().x/2;
    button_size->y = tekstura.getSize().y/2;
    setOrigin(Vector2f(button_size->x, button_size->y));
    setPosition(*position);
    setColor(Color(255, 255, 255, 230));
}

Button::Button(){}

void Button::konstruktor(int x, int y, string name){
    position->x = x;
    position->y = y;
    if(!tekstura.loadFromFile("img/" + name + ".png")){
        cout << "Cannot load button from file " << name << endl;
    }else{
        tekstura.loadFromFile("img/" + name + ".png");
    }
    setTexture(tekstura);
    button_size->x = tekstura.getSize().x/2;
    button_size->y = tekstura.getSize().y/2;
    setOrigin(Vector2f(button_size->x, button_size->y));
    setPosition(*position);
    setColor(Color(255, 255, 255, 230));
}

bool Button::isPressed(RenderWindow* window){
    *mouse_position_relative_to_window = Mouse::getPosition(*window);
    *mouse_position = window->mapPixelToCoords(*mouse_position_relative_to_window);
    if((mouse_position->x >= (position->x - button_size->x)) &&
    (mouse_position->x <= (position->x + button_size->x)) &&
    (mouse_position->y >= (position->y - button_size->y)) &&
    (mouse_position->y <= (position->y + button_size->y))){
        setColor(Color(255, 255, 255, 255));
        if(Mouse::isButtonPressed(Mouse::Left)){
            return true;
        }else{
            return false;
        }
    }else{
        setColor(Color(255, 255, 255, 230));
        return false;
    }
}