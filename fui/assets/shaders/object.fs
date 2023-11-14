#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform vec3 color;
uniform sampler2D oTexture;
uniform int hasTexture;

void main()
{
    if(hasTexture == 1){
        FragColor = texture(oTexture, texCoord);
    }
    else{
        FragColor = vec4(color, 1.0);
    }
}