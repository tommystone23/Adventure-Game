#include "imageloader.h"

# if SDL_BYTEORDER == SDL_BIG_ENDIAN
#  define RMASK 0xff000000
#  define GMASK 0x00ff0000
#  define BMASK 0x0000ff00
#  define AMASK 0x000000ff
# else
#  define RMASK 0x000000ff
#  define GMASK 0x0000ff00
#  define BMASK 0x00ff0000
#  define AMASK 0xff000000
# endif

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#define STB_RECT_PACK_IMPLEMENTATION
#include "stb/stb_rect_pack.h"

bool ImageLoader::load_texture(const char *file_path, struct GLTexture *texture_out)
{
    GLTexture texture = {};

    int number_of_channels;

    // Load texture
    unsigned char *texture_data = stbi_load(file_path, &texture.width, &texture.height, &number_of_channels, STBI_rgb_alpha);
    if(texture_data)
    {
        // Generate and bind texture to the type (GL_TEXTURE_2D)
        glGenTextures(1, &texture.id);
        glBindTexture(GL_TEXTURE_2D, texture.id);
        // Upload texture data
        // Pass GL_RGBA for both parameters to include alpha values in texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
        // Set texture wrapping and filtering options
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE /*GL_REPEAT*/);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE /*GL_REPEAT*/);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // GL_NEAREST fixes texture edge flickering!!!
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    else
    {
        printf("Failed to open texture data");
        return false;
    }

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(texture_data);

    if(texture_out)
        *texture_out = texture;

    return true;

}