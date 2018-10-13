#version 330 core

in vec3 fragPos;
in vec3 objNormalize;
in vec2 aTexCoord;

struct Material{

	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light{
	vec3 position;

	vec3 ambine;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;

uniform vec3 ambineColor;
uniform vec3 lightColor;

uniform vec3 lightPos;

uniform vec3 cameraPos;

out vec4 FragColor;

void main(){
	vec3 lightDir = normalize(fragPos - light.position);
	vec3 reflectVec = reflect(-lightDir,objNormalize);
	vec3 cameraVec = normalize(cameraPos - fragPos);

	float specularAmount = pow(max(dot(reflectVec,cameraVec),0),material.shininess);

	vec3 diffuse = texture(material.diffuse,aTexCoord).xyz  * max(dot(lightDir,objNormalize),0) * light.diffuse;
	vec3 specular = texture(material.specular,aTexCoord).xyz * specularAmount * light.specular;	
	vec3 ambine = light.ambine * texture(material.diffuse,aTexCoord).xyz;

	FragColor = vec4((ambine +  diffuse + specular)  ,1.0f);
}