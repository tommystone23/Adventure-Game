#include "renderer.h"
#include <algorithm>
#include "spritebatch.h"

Renderer::Renderer(Window *window)
    : GameObject(),
    _sprite_batch(NULL),
    _window(window),
    _camera(NULL)
{
    set_identifier("Renderer");

    _camera = new Camera2D();
    _camera->init(_window->get_width(), _window->get_height());
    _camera->set_scale(1.0f);
    _camera->set_position(glm::vec2(0.0f, 0.0f));
}

void Renderer::init()
{
    _sprite_batch = new SpriteBatch();
    _sprite_batch->init();
}

bool Renderer::create_shaders()
{
    Shader *shader = new Shader();
    bool insert = shader->create_shaders("shaders/basic_shader.vert", "shaders/basic_shader.frag");
    if(insert)
        _shaders.insert(std::pair<ShaderType, Shader*>(SHADER_BASIC, shader));
    else 
    {
        error() << "failed to create basic shader";
        return false;
    }

    _current_shader = shader;

    return true;
}

void Renderer::shader_make_current(ShaderType shader_type)
{
    _current_shader = _shaders.at(shader_type);
}

GLTexture Renderer::load_texture(const char *texture_file_path)
{
    GLTexture texture = {};
    ImageLoader::load_texture(texture_file_path, &texture);
    return texture;
}

void Renderer::draw(const glm::vec4 &dest_rect, const glm::vec4 &uv_rect, 
                    GLuint texture_id, const Color &color)
{
    _sprite_batch->begin();
    _sprite_batch->draw(dest_rect, uv_rect, texture_id, 0.0f, color);
}

void Renderer::render()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    _sprite_batch->end();

    _current_shader->use();
    _current_shader->set_uniform_mat4("projection", _camera->get_camera_matrix());
    _sprite_batch->render_batch();
    _current_shader->unuse();

    _window->swap_buffers();
}