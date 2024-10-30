#include "worldgenerator.h"
#include <random>
#include <ctime>

WorldGenerator::WorldGenerator(float tile_length, int width, int height)
    : _tile_length(tile_length),
    _width(width),
    _height(height)
{

}

bool WorldGenerator::generate_world(int nb_steps)
{
    allocate_tile_data();
    random_walk_generate_world(nb_steps);

    return true;
}

void WorldGenerator::allocate_tile_data()
{
    _tile_data.resize(_height);
    for(size_t i = 0; i < _tile_data.size(); i++)
    {
        _tile_data[i].resize(_width);
        for(size_t j = 0; j < _tile_data[i].size(); j++)
        {
            Tile *tile = &_tile_data[i][j];
            glm::vec2 pos_scaled = { i * _tile_length, j * _tile_length };
            tile->position = pos_scaled;
        }
    }
}

void WorldGenerator::destroy_tile_data()
{
    for(size_t i = 0; i < _tile_data.size(); i++)
    {
        _tile_data[i].clear();
    }
    _tile_data.clear();
}

void WorldGenerator::random_walk_generate_world(int nb_steps)
{
    // Position ourselves in centre of map, and generate outwards
    glm::vec2 cur_pos = { (_width / 2), (_height / 2) };

    _tile_data[(int)cur_pos.y][(int)cur_pos.x].position = cur_pos;
    _tile_data[(int)cur_pos.y][(int)cur_pos.x].type = GRASS;

    glm::vec2 allowed_movements[4] = {
        { 0.0f, 1.0f }, // up
        { 0.0f, -1.0f }, // down
        { -1.0f, 0.0f }, // left
        { 1.0f, 0.0f } // right
    };

    std::mt19937 random_engine;
    random_engine.seed(time(nullptr));
    std::uniform_int_distribution<int> rand_movement(0, 3);

    for(int i = 0; i < nb_steps; i++)
    {
        while(true)
        {
            glm::vec2 new_pos = cur_pos + allowed_movements[rand_movement(random_engine)];

            if(new_pos.x >= 0 && new_pos.x < _width && new_pos.y >= 0 && new_pos.y < _height)
            {
                _tile_data[(int)new_pos.y][(int)new_pos.x].type = GRASS;

                cur_pos = new_pos;

                break;
            }
        }
    }
    // Fill in water where blank spaces are
    for(size_t i = 0; i < _tile_data.size(); i++)
    {
        for(size_t j = 0; j < _tile_data[i].size(); j++)
        {
            Tile *tile = &_tile_data[i][j];
            if(tile->type == NONE)
                tile->type = WATER;
        }
    }
}