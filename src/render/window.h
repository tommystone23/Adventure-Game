#ifndef WINDOW_H
#define WINDOW_H

extern "C" 
{
#include "glad/glad.h"
}
#include <SDL2/SDL.h>
#include "../utils/gameobject.h"

class Window : public GameObject
{
public:
    Window();
    ~Window();

    bool init(const char *name, int width, int height);
    void destroy();

    void swap_buffers();

    SDL_Window* get_window() const { return _window; }
    int get_width() const { return _width; }
    int get_height() const { return _height; }

private:
    SDL_Window *_window;
    SDL_GLContext _opengl_ctx;

    int _width;
    int _height;
};

#endif //WINDOW_H