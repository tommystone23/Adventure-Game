#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class InputManager;

class Player : public Entity
{
public:
    Player(glm::vec4 start_rect, Renderer *renderer, InputManager *input_manager);
    ~Player() {}

    glm::vec2 get_position() const { return glm::vec2(_pos_rect.x, _pos_rect.y ); }

    virtual void update();
    virtual void draw();
private:
    float _speed;

    Renderer *_renderer;
    InputManager *_input_manager;
};

#endif // PLAYER_H