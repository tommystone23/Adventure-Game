#include "game.h"
#include "render/window.h"
#include "render/renderer.h"
#include "utils/inputmanager.h"
#include "world/worldgenerator.h"
#include "entities/player.h"
#include "world/world.h"

Game::Game()
    : GameObject(),
    _state(STARTING),
    _window(NULL),
    _renderer(NULL),
    _input_manager(NULL),
    _world(NULL)
{
    set_identifier("Game");
}

Game::~Game()
{

}

bool Game::init()
{
    _window = new Window();
    if(!_window->init("2D Adventure", 1920, 1080)) 
    {
        error() << "unable to init window";
        return false; 
    }

    _renderer = new Renderer(_window);
    _renderer->init();
    if(!_renderer->create_shaders())
    {
        error() << "failed to create shaders";
        return false;
    }
    _input_manager = new InputManager();

    _world = new World(_renderer, _input_manager);
    _world->init(100, 100);

    return true;
}

void Game::run()
{
    while(_state != QUIT)
    {
        check_input();
        update();
        render();
    }
}

void Game::check_input()
{
    _input_manager->get_input(&_state);
}

void Game::update()
{
    _world->update();
}

void Game::render()
{
    _world->draw();
    _renderer->render();
}