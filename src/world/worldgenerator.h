#ifndef WORLD_GENERATOR_H
#define WORLD_GENERATOR_H

#include <glm/glm.hpp>

enum TileType
{
    NONE,
    GRASS,
    WATER
};

struct Tile
{
    glm::vec2 position = { 0.0f, 0.0f };
    TileType type = NONE;
};

class WorldGenerator
{
public:
    WorldGenerator(int width, int height);
    ~WorldGenerator() { destroy_tile_data(); }

    bool generate_world(int nb_steps);

    Tile** get_world_data() { return _tile_data; }

private:
    Tile** _tile_data;

    int _width;
    int _height;

    void allocate_tile_data();
    void destroy_tile_data();
    void random_walk_generate_world(int nb_steps);
};

#endif // WORLD_GENERATOR_H