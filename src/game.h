#ifndef GAME_H
#define GAME_H

#include "utils/gameobject.h"
#include "render/imageloader.h"

class Window;
class Renderer;
class InputManager;
class WorldGenerator;
class Player;

enum GameState
{
    STARTING,
    RUNNING,
    QUIT
};

class Game : public GameObject
{
public:
    Game();
    ~Game();

    bool init();
    void run();

private:
    GameState _state;

    Window *_window;
    Renderer *_renderer;
    InputManager *_input_manager;
    WorldGenerator *_world_generator;

    GLTexture _grass_texture;
    GLTexture _water_texture;
    Player *_player;

    void check_input();
    void update();
    void render();
};

#endif //GAME_H