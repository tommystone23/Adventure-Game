#include "player.h"
#include "../utils/inputmanager.h"
#include "../render/renderer.h"
#include <SDL2/SDL.h>

Player::Player(glm::vec4 start_rect, Renderer *renderer, InputManager *input_manager)
    : Entity(),
    _renderer(renderer),
    _input_manager(input_manager)
{
    set_identifier("Player");

    if(!ImageLoader::load_texture("textures/Cute_Fantasy_Free/Player/Player.png", &_texture))
        info() << "unable to open texture for player";

    _pos_rect = start_rect;
    _speed = 2.0f;
    float texture_width_pixels = _texture.width / 6;
    float texture_height_pixels = _texture.height / 10;
    // Hardcode UV coordinates for now
    _uv_rect = { 0.0f, 
        (1.0f - (texture_height_pixels / _texture.height)), 
        (texture_width_pixels / (float)_texture.width), 
        (texture_height_pixels / (float)_texture.height) 
    };
    _color = { 255, 255, 255, 255 };
}

void Player::update()
{
    glm::vec2 movement_direction(0.0f);
    if(_input_manager->is_key_down(SDLK_w))
        movement_direction.y += 1;
    if(_input_manager->is_key_down(SDLK_a))
        movement_direction.x -= 1;
    if(_input_manager->is_key_down(SDLK_s))
        movement_direction.y -= 1;
    if(_input_manager->is_key_down(SDLK_d))
        movement_direction.x += 1;
    
    if(glm::length(movement_direction))
    {
        glm::vec2 movement_vec = glm::normalize(movement_direction) * _speed;
        _pos_rect.x += movement_vec.x;
        _pos_rect.y += movement_vec.y;
    }
}

void Player::draw()
{
    _renderer->draw(_pos_rect, _uv_rect, _texture.id, _color);
}