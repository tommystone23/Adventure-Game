#ifndef RENDERER_H
#define RENDERER_H

#include "glad/glad.h"
#include "../utils/gameobject.h"
#include <glm/glm.hpp>
#include <map>
#include "shader.h"
#include "window.h"
#include "imageloader.h"
#include "camera2d.h"
#include "vertex.h"
#include <vector>

class SpriteBatch;

enum ShaderType
{
    SHADER_BASIC = 0
};

class Renderer : public GameObject
{
public:
    Renderer(Window *window);
    ~Renderer() {}

    void init();
    bool create_shaders();
    void shader_make_current(ShaderType shader_type);

    GLTexture load_texture(const char *texture_file_path);

    void draw(const glm::vec4 &dest_rect, const glm::vec4 &uv_rect, 
                    GLuint texture_id, const Color &color);
    void render();

    Camera2D* camera() { return _camera; }

private:
    SpriteBatch *_sprite_batch;

    Window *_window;
    Camera2D *_camera;

    std::map<ShaderType, Shader*> _shaders;
    Shader *_current_shader;
};

#endif // RENDERER_H