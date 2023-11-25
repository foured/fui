#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aSize;
layout (location = 3) in vec3 aOffset;

out vec2 texCoord;

void main()
{    
    vec3 pos = aPos * aSize + aOffset;
    vec3 FragPos = vec3(mat4(1.0) * vec4(pos, 1.0));
    gl_Position = vec4(FragPos, 1.0);

    texCoord = aTexCoord;
}