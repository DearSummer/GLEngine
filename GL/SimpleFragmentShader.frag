#version 330 core
out vec4 FragColor;
in vec2 aTexCoord;

uniform vec3 color;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main(){
	vec3 result = texture(texture1,aTexCoord).xyz;
	result += texture(texture2,aTexCoord).xyz;

	FragColor = vec4(result,1.0f);
}