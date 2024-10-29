#version 330 core
out vec4 FragColor;

in vec4 outColor;
in vec2 outUV;

uniform sampler2D Texture;

void main()
{
    vec4 player_texture = texture(Texture, outUV);
    FragColor = (player_texture * outColor);
}