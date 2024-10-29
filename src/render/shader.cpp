#include "shader.h"

Shader::Shader()
    : GameObject()
{
    set_identifier("Shader");
}

Shader::~Shader()
{

}

void Shader::use()
{
    glUseProgram(_program_id);
}

void Shader::unuse()
{
    glUseProgram(0);
}

bool Shader::create_shaders(const char *vertex_shader_path, const char *fragment_shader_path)
{
    _program_id = glCreateProgram();
    GLuint vert_shader_id = glCreateShader(GL_VERTEX_SHADER);
    if(!vert_shader_id) 
    {
        error() << "failed to create vertex shader id";
        return false;
    }

    GLuint frag_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    if(!frag_shader_id)
    {
        error() << "failed to create fragment shader id";
        return false;
    }

    bool ret = false;
    ret = compile_shader(vert_shader_id, vertex_shader_path);
    if(!ret)
    {
        error() << "failed to compile vertex shader" << vertex_shader_path;
        return false;
    }

    ret = compile_shader(frag_shader_id, fragment_shader_path);
    if(!ret)
    {
        error() << "failed to compile fragment shader" << fragment_shader_path;
        return false;
    }

    ret = link_shaders(vert_shader_id, frag_shader_id);
    if(!ret)
    {
        error() << "failed to link shaders" << vertex_shader_path << fragment_shader_path;
        return false;
    }

    return true;
}

bool Shader::compile_shader(GLuint id, const char *shader_path)
{
    FILE *f = fopen(shader_path, "rb");
    if(!f) {
        error() << "failed to open file" << shader_path;
        return false;
    }

    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buf = (char*)malloc((length + 1) * sizeof(char));
    if(!buf) {
        error() << "failed to initialize buffer";
        return false;
    }
    size_t bytes_read = fread(buf, 1, length, f);
    if(bytes_read != length) {
        error() << "failed to read all bytes in file" << shader_path;
        return false;
    }
    buf[length] = '\0';

    fclose(f);

    glShaderSource(id, 1, (const char *const *)&buf, NULL);
    glCompileShader(id);

    free(buf);

    GLint success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE)
    {
        GLint max_buffer = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &max_buffer);
        char *error_str = (char*)malloc(max_buffer * sizeof(char));
        if(!error_str) {
            error() << "failed to allocate error buffer";
            return false;
        }
        glGetShaderInfoLog(id, max_buffer, &max_buffer, error_str);

        glDeleteShader(id);

        error() << "Unable to compile shader" << shader_path << "due to: " << error_str;
        free(error_str);
        return false;
    }

    return true;
}

bool Shader::link_shaders(GLuint vert_id, GLuint frag_id)
{
    glAttachShader(_program_id, vert_id);
    glAttachShader(_program_id, frag_id);

    glLinkProgram(_program_id);

    GLint is_linked = 0;
    glGetProgramiv(_program_id, GL_LINK_STATUS, (int*)&is_linked);
    if(is_linked == GL_FALSE)
    {
        GLint max_buffer = 0;
        glGetProgramiv(_program_id, GL_INFO_LOG_LENGTH, &max_buffer);
        char error[max_buffer];
        glGetProgramInfoLog(_program_id, max_buffer, &max_buffer, error);

        glDeleteProgram(_program_id);
        glDeleteShader(vert_id);
        glDeleteShader(frag_id);

        return false;
    }

    glDetachShader(_program_id, vert_id);
    glDetachShader(_program_id, frag_id);

    return true;
}

void Shader::set_uniform_mat4(const char *name, glm::mat4 mat)
{
    glUniformMatrix4fv(glGetUniformLocation(_program_id, name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::set_uniform_float(const char *name, float value)
{

}

void Shader::set_uniform_int(const char *name, int value)
{

}

void Shader::set_uniform_uint(const char *name, unsigned int value)
{

}

void Shader::set_uniform_vec2(const char *name, glm::vec2 vec)
{

}

void Shader::set_uniform_vec3(const char *name, glm::vec3 vec)
{

}

void Shader::set_uniform_vec4(const char *name, glm::vec4 vec)
{

}