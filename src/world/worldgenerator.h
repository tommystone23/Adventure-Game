#ifndef WORLD_GENERATOR_H
#define WORLD_GENERATOR_H

#include <glm/glm.hpp>
#include <vector>

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
    WorldGenerator(float tile_length, int width, int height);
    ~WorldGenerator() { destroy_tile_data(); }

    bool generate_world(int nb_steps);

    std::vector<std::vector<Tile>> get_world_data() { return _tile_data; }

private:
    std::vector<std::vector<Tile>> _tile_data;

    float _tile_length;
    int _width;
    int _height;

    void allocate_tile_data();
    void destroy_tile_data();
    void random_walk_generate_world(int nb_steps);
};

#endif // WORLD_GENERATOR_H