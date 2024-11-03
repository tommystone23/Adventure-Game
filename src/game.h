#ifndef GAME_H
#define GAME_H

#include "utils/gameobject.h"

class Window;
class Renderer;
class InputManager;
class World;

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
    World *_world;

    void check_input();
    void update();
    void render();
};

#endif //GAME_H