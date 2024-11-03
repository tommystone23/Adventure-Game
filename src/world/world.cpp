#include "world.h"
#include "worldgenerator.h"
#include "../render/renderer.h"
#include "../utils/inputmanager.h"
#include "../entities/player.h"

World::World(Renderer *renderer, InputManager *input_manager)
    : GameObject(),
    _player(NULL),
    _world_generator(NULL),
    _renderer(renderer),
    _input_manager(input_manager)
{
    set_identifier("World");
}

World::~World()
{
    delete _world_generator;
}

void World::init(int world_width, int world_height)
{
    _world_generator = new WorldGenerator(TILE_LENGTH, world_width, world_height);
    _world_generator->generate_world((world_width * world_height) / 2);

    _grass_texture = _renderer->load_texture("textures/Cute_Fantasy_Free/Tiles/Grass_Middle.png");
    _water_texture = _renderer->load_texture("textures/Cute_Fantasy_Free/Tiles/Water_Middle.png");

    glm::vec4 player_centre_rect = { (world_width / 2) * TILE_LENGTH, (world_height / 2) * TILE_LENGTH, TILE_LENGTH, TILE_LENGTH };
    _player = new Player(player_centre_rect, _renderer, _input_manager);
}

void World::update()
{
    _player->update();
    _input_manager->update();
    _renderer->camera()->set_position(_player->get_position());
    _renderer->camera()->update();
}

void World::draw()
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
}
