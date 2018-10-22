#version 330 core
layout(location = 5) in vec3 pos;
layout(location = 6) in vec2 texCoord;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

out vec2 aTexCoord;

void main(){
	gl_Position = projectionMat *  viewMat * modelMat *  vec4(pos,1.0f);
	aTexCoord = texCoord;
}