#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aSize;
layout (location = 3) in vec3 aOffset;

out vec2 texCoord;

void main()
{    
    vec3 pos = aPos * (aSize + vec3(0.01)) + aOffset;
    //vec3 pos = vec3(aPos.x * aSize.x + aOffset.x, aPos.y + aOffset.y, aPos.x + aOffset.z);
    vec3 FragPos = vec3(mat4(1.0) * vec4(pos, 1.0));
    gl_Position = vec4(FragPos, 1.0);

    texCoord = aTexCoord;
}