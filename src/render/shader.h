#ifndef SHADER_h
#define SHADER_H

#include "glad/glad.h"
#include "../utils/gameobject.h"
#include <glm/glm.hpp>

class Shader : public GameObject
{
public:
    Shader();
    ~Shader();

    void use();
    void unuse();
    bool create_shaders(const char *vertex_shader_path, const char *fragment_shader_path);

    void set_uniform_mat4(const char *name, glm::mat4 mat);
    void set_uniform_float(const char *name, float value);
    void set_uniform_int(const char *name, int value);
    void set_uniform_uint(const char *name, unsigned int value);
    void set_uniform_vec2(const char *name, glm::vec2 vec);
    void set_uniform_vec3(const char *name, glm::vec3 vec);
    void set_uniform_vec4(const char *name, glm::vec4 vec);

private:
    GLuint _program_id;

    bool compile_shader(GLuint id, const char *shader_path);
    bool link_shaders(GLuint vert_id, GLuint frag_id);
};

#endif // SHADER_H