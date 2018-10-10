#version 330 core

in vec3 fragPos;
in vec3 objNormalize;

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

	float specularAmount = pow(max(dot(reflectVec,cameraVec),0),32);
	vec3 specular = specularAmount * lightColor;

	vec3 diffuse = max(dot(lightDir,objNormalize),0) * lightColor;
	FragColor = vec4((ambineColor +  diffuse + specular) * objColor ,1.0f);
}