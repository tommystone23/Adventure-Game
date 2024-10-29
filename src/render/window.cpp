#include "window.h"

Window::Window()
    : GameObject(),
    _window(NULL),
    _width(0),
    _height(0)
{
    set_identifier("Window");
}

Window::~Window()
{
    destroy();
}

bool Window::init(const char *name, int width, int height)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        error() << "failed to initialize SDL";
        return false;
    }

    // Setup OpenGL Attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Create Window
    _window = SDL_CreateWindow(name, 0, 0, width, height, SDL_WINDOW_OPENGL);
    if(!_window)
    {
        error() << "failed to create SDL window";
        return false;
    }

    _width = width;
    _height = height;

    // Create Context
    _opengl_ctx = SDL_GL_CreateContext(_window);
    if(!_opengl_ctx)
    {
        error() << "failed to create context";
        return false;
    }

    // Make Current Context
    SDL_GL_MakeCurrent(_window, _opengl_ctx);

    // Initialize GLAD
    if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) 
    {
        error() << "failed to load GLAD";
        return false;
    }

    // Create View Port
    glViewport(0, 0, width, height);

    glClearColor(0.6f, 0.6f, 0.6f, 1.0f);

    // Turn Vsync on
    SDL_GL_SetSwapInterval(1);

    // Print OpenGL Version
    info() << "*** OpenGL Version: " << glGetString(GL_VERSION) << "***";

    // Enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

void Window::destroy()
{
    SDL_GL_DeleteContext(_opengl_ctx);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Window::swap_buffers()
{
    SDL_GL_SwapWindow(_window);
}