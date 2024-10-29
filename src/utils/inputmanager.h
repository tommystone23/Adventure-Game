/*
    Handles all player input. key_id parameters are SDL id's that
    will be accessible every frame. 
    Functions press_key, release_key, and set_mouse_coords should be called 
    in the SDLPollEvent loop. The other functions can be called by other
    game elements to check what buttons have been pressed that frame.
*/
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H
#include <unordered_map>
#include <glm/glm.hpp>
#include "../game.h"

class InputManager
{
public:
    InputManager();
    ~InputManager();

    void get_input(GameState *state_out);

    void update();

    bool is_key_down(unsigned int key_id);
    bool is_key_pressed(unsigned int key_id);

    glm::vec2 get_mouse_coords() const { return _mouse_coords; }
private: 
    std::unordered_map<unsigned int, bool> _key_map;
    std::unordered_map<unsigned int, bool> _previous_key_map;

    glm::vec2 _mouse_coords;

    void press_key(unsigned int key_id);
    void release_key(unsigned int key_id);
    bool was_key_down(unsigned int key_id);
    void set_mouse_coords(float x, float y);
};

#endif