#version 330 core      
layout(location = 0)in vec3 pos;
layout(location = 1)in vec3 aNormalize;
layout(location = 2)in vec2 texCoord;

out vec3 objNormalize;
out vec3 fragPos;
out vec2 aTexCoord;

uniform mat4 p;
uniform mat4 v;
uniform mat4 m;

void main(){
	gl_Position = p * v * m * vec4(pos.xyz,1.0f);
	objNormalize = mat3(transpose(inverse(m))) * aNormalize;
	fragPos = (m * vec4(pos,1.0f)).xyz;
	aTexCoord = texCoord;
}