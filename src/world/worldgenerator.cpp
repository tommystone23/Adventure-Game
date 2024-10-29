#include "worldgenerator.h"
#include <random>
#include <ctime>

WorldGenerator::WorldGenerator(int width, int height)
    : _tile_data(NULL),
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
    _tile_data = new Tile*[_height];
    for(int i = 0; i < _height; i++)
    {
        _tile_data[i] = new Tile[_width];
    }
}

void WorldGenerator::destroy_tile_data()
{
    for(int i = 0; i < _height; i++)
    {
        delete[] _tile_data[i];
    }

    delete[] _tile_data;
}

void WorldGenerator::random_walk_generate_world(int nb_steps)
{
    // Position ourselves in centre of map
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
                _tile_data[(int)new_pos.y][(int)new_pos.x].position = new_pos;
                _tile_data[(int)new_pos.y][(int)new_pos.x].type = GRASS;

                cur_pos = new_pos;

                break;
            }
        }
    }
}