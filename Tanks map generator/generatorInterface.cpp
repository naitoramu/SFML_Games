#include "generatorInterface.hpp"

using namespace sf;
using namespace std;

GeneratorInterface::GeneratorInterface(RenderWindow* window, Vector2f* middle, Vector2f* resolution){
    this->window = window;
    net.setTextureAndPosition(middle, resolution);
    background_texture.loadFromFile("img/generator_background.png");
    background_sprite.setTexture(background_texture);
    background_sprite.setOrigin(Vector2f(background_texture.getSize().x/2, background_texture.getSize().y/2));
    background_sprite.setPosition(*middle);
}

void GeneratorInterface::cellNumber(){
    i_x = 0;
    i_y = 0;
    cell_position->x = mouse_position->x;
    cell_position->y = mouse_position->y;
    while(cell_position->x > 60){
        cell_position->x -= 60;
        i_x += 1;
    }
    while(cell_position->y > 60){
        cell_position->y -= 60;
        i_y += 1;
    }

    cell_position->x = i_x * 60 + 30;
    cell_position->y = i_y * 60 + 30;
}

int GeneratorInterface::cellIsPressed(){
    *mouse_position_relative_to_window = Mouse::getPosition(*window);
    *mouse_position = window->mapPixelToCoords(*mouse_position_relative_to_window);
    if(Mouse::isButtonPressed(Mouse::Left) && mouse_position->x >= 0 && mouse_position->y >= 0){
        cellNumber();
        obstacles[i_y][i_x] = true;
        return 1;
    }else if(Mouse::isButtonPressed(Mouse::Right) && mouse_position->x >= 0 && mouse_position->y >= 0){
        cellNumber();
        obstacles[i_y][i_x] = false;
        return 2;
    }else{
        return 0;
    }   
}

string GeneratorInterface::drawingTextBox(Font* font){
    Text user_text("Podaj nazwe mapy", *font, 50);
    String user_input;
    bool end = false;
    Event event;
    while(!end){
        while(window->pollEvent(event)){
            if (event.type == sf::Event::TextEntered){
                user_input += event.text.unicode;
                user_text.setString(user_input);
            }
            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Return){
                end = true;
                return user_input;
            }
        }
    window->draw(user_text);
    window->display();
    }
}

void GeneratorInterface::mapReset(){
    for(int i = 0; i < 18; i++){
        for(int j = 0; j < 32; j++){
            obstacles[i][j] = false;
            obstacle[i][j].setPosition(-60, -60);
        }
    }
}

bool GeneratorInterface::display(bool* open_menu){
    Font* font = new Font;
    if(!font->loadFromFile("fonts/Oxanium-Medium.ttf")){
        cout << "Cannot load font" << endl;
    }else{
        font->loadFromFile("fonts/Oxanium-Medium.ttf");
    }
    while(window->isOpen()){
        Event event;
        while (window->pollEvent(event)){
            if(event.type == Event::Closed){
                window->close();
            }if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape){
                *open_menu = true;
                mapReset();
                return 0;
            }if(cellIsPressed() == 1){
                obstacle[i_y][i_x].setPosition(cell_position->x, cell_position->y);
            }else if(cellIsPressed() == 2){
                obstacle[i_y][i_x].setPosition(-61, -61);
            }
            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Return){
                map_name = drawingTextBox(font);
                SaveFile map(map_name);
                for(int i = 0; i < 18; i++){
                    for(int j = 0; j < 32; j++){
                        map << obstacles[i][j];
                    }
                }
                map.close();
                mapReset();
            }
        }

        window->clear();
        window->draw(background_sprite);
        window->draw(net);
        for(int i = 0; i < 18; i++){
            for(int j = 0; j < 32; j++){
                window->draw(obstacle[i][j]);
            }
        }
        window->display();
    }
}