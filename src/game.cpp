#include "game.h"
#include "render/window.h"
#include "render/renderer.h"
#include "utils/inputmanager.h"
#include "world/worldgenerator.h"
#include "entities/player.h"

// const static float TILE_LENGTH = 48.0f;

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
    _grass_texture = _renderer->load_texture("textures/Cute_Fantasy_Free/Tiles/Grass_Middle.png");
    _water_texture = _renderer->load_texture("textures/Cute_Fantasy_Free/Tiles/Water_Middle.png");

    _input_manager = new InputManager();

    _world_generator = new WorldGenerator(TILE_LENGTH, 100, 100);
    _world_generator->generate_world(50000);

    _player = new Player(glm::vec4(50.0f * TILE_LENGTH, 50.0f * TILE_LENGTH, TILE_LENGTH, TILE_LENGTH),
                        _renderer, _input_manager);

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
    _player->update();
    _input_manager->update();
    _renderer->camera()->set_position(_player->get_position());
    _renderer->camera()->update();
}

void Game::render()
{
    glm::vec4 ground_uv_rect = { 0.0f, 0.0f, 1.0f, 1.0f };
    Color color = { 255, 255, 255, 255 };

    std::vector<std::vector<Tile>> tile_data = _world_generator->get_world_data();
    Camera2D *camera = _renderer->camera();
    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j < 100; j++)
        {
            Tile tile = tile_data[i][j];
            glm::vec4 tile_dest_rect = { tile.position.x, tile.position.y, TILE_LENGTH, TILE_LENGTH };
            if(tile.type == GRASS)
            {
                if(camera->is_in_view(glm::vec2(tile_dest_rect.x, tile_dest_rect.y), glm::vec2(tile_dest_rect.z, tile_dest_rect.w)))
                    _renderer->draw(tile_dest_rect, ground_uv_rect, _grass_texture.id, color);
            }
            if(tile.type == WATER)
            {
                if(camera->is_in_view(glm::vec2(tile_dest_rect.x, tile_dest_rect.y), glm::vec2(tile_dest_rect.z, tile_dest_rect.w)))
                    _renderer->draw(tile_dest_rect, ground_uv_rect, _water_texture.id, color);
            }
        }
    }

    _player->draw();
    _renderer->render();
}