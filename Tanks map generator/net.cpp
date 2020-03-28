#include "net.hpp"
#include <iostream>

using namespace std;
using namespace sf;

Net::Net(){}

Net::Net(Vector2f* middle, Vector2f* resolution){
    if(!tekstura.loadFromFile("img/net.png")){
        cout << "Cannot load net" << endl;
    }else{
        tekstura.loadFromFile("img/net.png");
    }
    setTexture(tekstura);
    setOrigin(Vector2f(tekstura.getSize().x/2, tekstura.getSize().y/2));
    setPosition(*middle);
}

void Net::setTextureAndPosition(Vector2f* middle, Vector2f* resolution){
    if(!tekstura.loadFromFile("img/net.png")){
        cout << "Cannot load net" << endl;
    }else{
        tekstura.loadFromFile("img/net.png");
    }
    setTexture(tekstura);
    setOrigin(Vector2f(tekstura.getSize().x/2, tekstura.getSize().y/2));
    setPosition(*middle);
}