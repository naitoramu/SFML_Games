#include "menu.hpp"

using namespace std;
using namespace sf;

Menu::Menu(RenderWindow* window, int buttons_count, int x, int y, int space){
    this->window = window;
    this->buttons_count = buttons_count;
    button = new Button[buttons_count];
    for(int i = 0; i < buttons_count; i++){
        button[i].konstruktor(x, y, "button" + to_string(i));
        y += space;
    }
    backgroung_texture.loadFromFile("img/menu_background.png");
    background_sprite.setTexture(backgroung_texture);
    background_sprite.setOrigin(Vector2f(backgroung_texture.getSize().x/2, backgroung_texture.getSize().y/2));
    background_sprite.setPosition(Vector2f(960, 540));
}

bool Menu::display(int* input){
    while(window->isOpen()){
        Event event;
        while (window->pollEvent(event)){
            if(event.type == Event::Closed){
                window->close();
            }else if(button[0].isPressed(window)){
                *input = 0;
                return 0;
            }else if(button[1].isPressed(window)){
                *input = 1;
                return 0;
            }else if(button[2].isPressed(window)){
                *input = 2;
                return 0;
            }
        }

        window->clear();
        window->draw(background_sprite);
        for(int i = 0; i < buttons_count; i++){
            window->draw(button[i]);
        }
        window->display();
    }
}