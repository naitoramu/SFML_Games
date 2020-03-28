#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Net : public Sprite{
    public:
    Texture tekstura;
    Net();
    Net(Vector2f*, Vector2f*);
    void setTextureAndPosition(Vector2f*, Vector2f*);
};