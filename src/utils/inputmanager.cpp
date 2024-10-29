#include "inputmanager.h"
#include <SDL2/SDL.h>

InputManager::InputManager() 
    : _mouse_coords(0.0f)
{
}

InputManager::~InputManager()
{
}

void InputManager::get_input(GameState *state_out)
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case(SDL_QUIT):
                *state_out = QUIT;
                break;
            case(SDL_MOUSEMOTION):
                set_mouse_coords(event.motion.x, event.motion.y);
                break;
            case(SDL_KEYDOWN):
                press_key(event.key.keysym.sym);
                break;
            case(SDL_KEYUP):
                release_key(event.key.keysym.sym);
                break;
            case(SDL_MOUSEBUTTONDOWN):
                press_key(event.button.button);
                break;
            case(SDL_MOUSEBUTTONUP):
                release_key(event.button.button);
                break;
        }
    }
}

void InputManager::update()
{
    for(auto &it : _key_map) {
        _previous_key_map[it.first] = it.second;
    }
}

void InputManager::press_key(unsigned int key_id)
{
    _key_map[key_id] = true;
}

void InputManager::release_key(unsigned int key_id)
{
    _key_map[key_id] = false;
}

// Returns true if key is held down
bool InputManager::is_key_down(unsigned int key_id)
{
    if(_key_map.find(key_id) != _key_map.end())
    {
        return _key_map[key_id];
    }
    return false;
}

// Returns true if key was just pressed
bool InputManager::is_key_pressed(unsigned int key_id)
{
    // Check if it was pressed this frame and not last frame
    bool is_pressed;
    if(is_key_down(key_id) && !was_key_down(key_id))
        return true;

    return false;
}

bool InputManager::was_key_down(unsigned int key_id)
{
    if(_previous_key_map.find(key_id) != _previous_key_map.end())
    {
        return _previous_key_map[key_id];
    }
    return false;
}

void InputManager::set_mouse_coords(float x, float y)
{
    _mouse_coords.x = x;
    _mouse_coords.y = y;
}
