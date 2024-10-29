#include "game.h"
#include "render/window.h"
#include "render/renderer.h"
#include "utils/inputmanager.h"
#include "world/worldgenerator.h"

Game::Game()
    : GameObject(),
    _state(STARTING),
    _window(NULL),
    _renderer(NULL),
    _input_manager(NULL)
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
    _texture = _renderer->load_texture("textures/sprites/characters/player.png");

    _input_manager = new InputManager();

    _world_generator = new WorldGenerator(1000, 1000);
    _world_generator->generate_world(500000);

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
    _input_manager->update();
    _renderer->camera()->update();
}

void Game::render()
{
    glm::vec4 dest_rect = { 500.0f, 500.0f, 48.0f, 48.0f };
    _renderer->camera()->set_position(glm::vec2(500.0f, 500.0f));
    glm::vec4 uv_rect = { 
        0.0f, 
        (1.0f - (48.0f / _texture.height)), 
        (48.0f / (float)_texture.width), 
        (48.0f / (float)_texture.height) 
    };
    Color color = { 255, 255, 255, 255 };

    Tile **tile_data = _world_generator->get_world_data();
    for(int i = 0; i < 1000; i++)
    {
        for(int j = 0; j < 1000; j++)
        {
            Tile tile = tile_data[i][j];
            if(tile.type == GRASS)
            {
                glm::vec4 tile_dest_rect = { tile.position.x, tile.position.y, 48.0f, 48.0f };
                _renderer->draw(tile_dest_rect, uv_rect, _texture.id, color);
            }
        }
    }

    _renderer->draw(dest_rect, uv_rect, _texture.id, color);
    _renderer->render();
}