#include "obstacle.hpp"

using namespace std;
using namespace sf;

Obstacle::Obstacle(){
    if(!tekstura.loadFromFile("img/obstacle.png")){
        cout << "Cannot load obstacle from file " << "obstacle.png" << endl;
    }else{
        tekstura.loadFromFile("img/obstacle.png");
    }
    setTexture(tekstura);
    origin->x = tekstura.getSize().x/2;
    origin->y = tekstura.getSize().y/2;
    setOrigin(*origin);
    setPosition(Vector2f(-61, -61));
}