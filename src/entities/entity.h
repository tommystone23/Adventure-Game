#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>
#include "../render/imageloader.h"
#include "../utils/gameobject.h"
#include "../render/vertex.h"

class Renderer;

const static float TILE_LENGTH = 48.0f;

class Entity : public GameObject
{
public:
    Entity(){}
    ~Entity(){}

protected:
    glm::vec4 _pos_rect;
    glm::vec4 _uv_rect;
    Color _color;
    GLTexture _texture;

    virtual void update(){}
    virtual void draw(){}
};

#endif //ENTITY_H