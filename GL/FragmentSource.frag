#version 330 core                   
in vec4 vertexcolor;                
in vec2 texCoord;
out vec4 FragColor;                 

uniform float mixValue;
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 objColor;
uniform vec3 ambientColor;

void main()                         
{                                   

	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * ambientColor;

	FragColor = vec4(ambient * objColor,1.0f) * 
		mix(texture(texture1,texCoord),texture(texture2,vec2(1.0 - texCoord.x,texCoord.y)), mixValue); 
}                                   