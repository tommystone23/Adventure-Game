#ifndef WORLD_H
#define WORLD_H

#include "../utils/gameobject.h"
#include "../render/imageloader.h"

class WorldGenerator;
class Renderer;
class InputManager;
class Player;

const static float TILE_LENGTH = 32.0f;

class World : public GameObject
{
public:
    World(Renderer *renderer, InputManager *input_manager);
    ~World();

    void init(int world_width, int world_height);
    void update();
    void draw();

private:
    Player *_player;
    WorldGenerator *_world_generator;
    Renderer *_renderer;
    InputManager *_input_manager;

    GLTexture _grass_texture;
    GLTexture _water_texture;
};

#endif // WORLD_H