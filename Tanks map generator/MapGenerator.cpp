#include <iostream>
#include <SFML/Graphics.hpp>
#include "generatorInterface.hpp"
#include "menu.hpp"

using namespace std;
using namespace sf;

bool openInstruction(Vector2f* middle, RenderWindow* window, bool* open_menu){
    Texture tekstura;
    Sprite background;
    if(!tekstura.loadFromFile("img/instruction.png")){
        cout << "Cannot load instruction" << endl;
    }else{
        tekstura.loadFromFile("img/instruction.png");
    }
    background.setTexture(tekstura);
    background.setOrigin(Vector2f(tekstura.getSize().x/2, tekstura.getSize().y/2));
    background.setPosition(*middle);

    window->draw(background);
    window->display();

    Event event;
    while (window->pollEvent(event))
    {
        if (event.type == Event::Closed){
            window->close();
        }
        if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape){
            *open_menu = true;
            return 0;
        }
    }
}

int main(){
    Vector2f resolution(1280, 720);
    RenderWindow window(VideoMode(resolution.x, resolution.y), "Tanks map generator", Style::Fullscreen);
    Vector2f middle(960, 540);
    window.setFramerateLimit(60);
    View view(Vector2f(960, 540), Vector2f(1920, 1080));
    window.setView(view);

    GeneratorInterface generator_interface(&window, &middle, &resolution);
    Menu menu(&window, 3, 960, 640, 150);
    int* input = new int;
    bool* open_menu = new bool;
    *open_menu = true;

    while (window.isOpen()){
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed){
                window.close();
            }
        }

        if(*open_menu) *open_menu = menu.display(input);
        if(!*(open_menu)){
            if(*input == 0){
                generator_interface.display(open_menu);
            }else if(*input == 1){
                openInstruction(&middle, &window, open_menu);
            }else if(*input == 2){
                window.close();
            }
        }
    }

    return 0;
}