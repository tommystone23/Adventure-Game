#version 330 core
layout (location = 0) in vec2 inPos;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec2 inUV;

out vec4 outColor;
out vec2 outUV;

uniform mat4 projection;

void main()
{
    gl_Position.xy = (projection * vec4(inPos, 0.0, 1.0)).xy;
    gl_Position.z = 0.0f;
    gl_Position.w = 1.0f;
    
    outColor = inColor;
    outUV = vec2(inUV.x, 1.0 - inUV.y);
}