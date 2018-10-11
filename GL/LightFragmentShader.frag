#version 330 core

in vec3 fragPos;
in vec3 objNormalize;

struct Material{
	vec3 ambine;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Material material;

uniform vec3 objColor;
uniform vec3 ambineColor;
uniform vec3 lightColor;

uniform vec3 lightPos;

uniform vec3 cameraPos;

out vec4 FragColor;

void main(){
	vec3 lightDir = normalize(fragPos - lightPos);
	vec3 reflectVec = reflect(-lightDir,objNormalize);
	vec3 cameraVec = normalize(cameraPos - fragPos);

	float specularAmount = pow(max(dot(reflectVec,cameraVec),0),material.shininess);
	vec3 specular = material.specular * specularAmount * lightColor;

	vec3 diffuse = material.diffuse * max(dot(lightDir,objNormalize),0) * lightColor;
	vec3 ambine = material.ambine * ambineColor;
	FragColor = vec4((ambine +  diffuse + specular) * objColor ,1.0f);
}