#include "SnakeHead.hpp"
#include "SnakeBody.hpp"
#include <iostream>

using namespace sf;

void SnakeHead::granice(){
    lim_l = (width - width_p) / 2;
    lim_g = (height - height_p) / 2;
    lim_r = lim_l + width_p;
    lim_d = lim_g + height_p;
}

SnakeHead::SnakeHead(){}

SnakeHead::SnakeHead(int sx, int sy, int wspx, int wspy, int h, int w, int scene_size){
    size_x = sx;
    size_y = sy;
    x = wspx;
    y = wspy;
    height = h;
    width = w;
    height_p = scene_size;
    width_p = scene_size;
    setSize(sf::Vector2f(size_x, size_y));
    setOrigin(size_x / 2, size_y / 2);
    setFillColor(sf::Color(35, 45, 20));
    setPosition(x, y);
    granice();
}

void SnakeHead::sterowanie(int z){
    if (z - previous_z != 2 && z - previous_z != -2)
        previous_z = z;
}

void SnakeHead::newPosition(){
    setPosition(x, y);
}

void SnakeHead::move(){
    if (previous_z == 4){
        x += size_x;
        newPosition();
    }
    else if (previous_z == 2){
        x -= size_x;
        newPosition();
    }
    else if (previous_z == 1){
        y += size_y;
        newPosition();
    }
    else if (previous_z == 3){
        y -= size_y;
        newPosition();
    }
}
bool SnakeHead::kolizja(SnakeBody* body, int segmenty){
    int a = 1, i = 0;
    if (((x < lim_l) || (x > lim_r) || (y < lim_g) || (y > lim_d)) && i == 0){
        //setPosition(body[0].getPosition());
        std::cout << "Kolizja!" << std::endl;
        return true;
    }
    else if ((x < lim_l) || (x > lim_r) || (y < lim_g) || (y > lim_d))
        a = 0;
    if (a){
        for (; i < segmenty; i++){
            if (getPosition() == body[i].getPosition())
                break;
        }
    }
    if (i == segmenty){
        return false;
    }
    else{
        std::cout << "Kolizja!" << std::endl;
        //setPosition(body[0].getPosition());
        return true;
    }
}