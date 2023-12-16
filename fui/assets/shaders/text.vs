#version 330 core
layout (location = 0) in vec4 vertex;
out vec2 TexCoord;

uniform mat4 proj;

void main(){
	gl_Position =  proj * vec4(vertex.xy, 0.0f, 1.0f);
	TexCoord = vertex.zw;
}