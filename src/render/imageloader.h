#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include "glad/glad.h"

struct GLTexture
{
    GLuint id = 0;
    int width;
    int height;
};

class ImageLoader
{
public:
    static bool load_texture(const char *file_path, struct GLTexture *texture_out);
};

#endif // IMAGELOADER_H