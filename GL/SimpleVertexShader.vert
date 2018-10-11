#version 330 core
layout(location = 5) in vec3 pos;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;


void main(){
	gl_Position = projectionMat *  viewMat * modelMat *  vec4(pos,1.0f);

}