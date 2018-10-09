#version 330 core                               
layout(location = 0) in vec3 aPos;              
//layout(location = 1) in vec3 aColor;        
layout(location = 2) in vec2 aTexCoord;

//uniform mat4 transform;
//uniform float offset;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

out vec4 vertexcolor;           
out vec2 texCoord;
void main()                                     
{                                               
gl_Position = projectionMat * viewMat * modelMat * vec4(aPos,1.0f);
vertexcolor = vec4(gl_Position.x,gl_Position.y,gl_Position.z,1.0f);
texCoord = aTexCoord;
}                                              