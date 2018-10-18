#version 330 core

in vec3 fragPos;
in vec3 objNormalize;
in vec2 aTexCoord;

struct Material{

	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct PointLight{
	vec3 position;

	vec3 ambine;
	vec3 diffuse;
	vec3 specular;


	float constant;
	float linear;
	float quadratic;
};

struct DirectionalLight{

	vec3 direction;
	//vec3 position;

	vec3 ambine;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight{
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	
	vec3 ambine;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;


uniform DirectionalLight directionalLight01;
uniform PointLight pointLight01;
uniform PointLight pointLight02;
uniform PointLight pointLight03;
uniform PointLight pointLight04;
uniform SpotLight spotLight01;
uniform SpotLight spotLight02;

uniform vec3 ambineColor;
uniform vec3 lightColor;

uniform vec3 lightPos;

uniform vec3 cameraPos;

uniform float time;

out vec4 FragColor;

vec3 calculatorSpotLight(SpotLight light){
	vec3 result;
	vec3 lightDir = normalize(light.position - fragPos);
	vec3 reflectVec = reflect(-lightDir,objNormalize);
	vec3 cameraVec = normalize(cameraPos - fragPos);
	
	float specularAmount = pow(max(dot(reflectVec,cameraVec),0),material.shininess);

	
	float theta = dot(lightDir,normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon , 0.0f,1.0f);

	vec3 diffuse = texture(material.diffuse,aTexCoord).xyz  * max(dot(lightDir,objNormalize),0) * light.diffuse * intensity;
	vec3 specular = texture(material.specular,aTexCoord).xyz * specularAmount * light.specular * intensity;	
	vec3 ambine = light.ambine * texture(material.diffuse,aTexCoord).xyz;

	result += diffuse;
	result += specular;
	result += ambine;

	return result;
}

vec3 calculatorDirectionalLight(DirectionalLight light){
	vec3 result;
	vec3 lightDir = normalize(-light.direction);
	vec3 reflectVec = reflect(lightDir,objNormalize);


	vec3 cameraVec = normalize(cameraPos - fragPos);

	float specularAmount = pow(max(dot(reflectVec,cameraVec),0),material.shininess);


	vec3 diffuse = texture(material.diffuse,aTexCoord).xyz  * max(dot(lightDir,objNormalize),0) * light.diffuse;
	vec3 specular = texture(material.specular,aTexCoord).xyz * specularAmount * light.specular;	
	vec3 ambine = light.ambine * texture(material.diffuse,aTexCoord).xyz;

	result += diffuse;
	result += specular;
	result += ambine;

	return result;
}

vec3 calculatorPointLight(PointLight light){
	vec3 result;
	vec3 lightDir = normalize(light.position - fragPos);
	vec3 reflectVec = reflect(-lightDir,objNormalize);
	vec3 cameraVec = normalize(cameraPos - fragPos);
	
	float specularAmount = pow(max(dot(reflectVec,cameraVec),0),material.shininess);

	float dist = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic *(dist * dist));

	
	vec3 diffuse = texture(material.diffuse,aTexCoord).xyz  * max(dot(lightDir,objNormalize),0) * light.diffuse * attenuation;
	vec3 specular = texture(material.specular,aTexCoord).xyz * specularAmount * light.specular * attenuation;	
	vec3 ambine = light.ambine * texture(material.diffuse,aTexCoord).xyz * attenuation;

	result += diffuse;
	result += specular;
	result += ambine;

	return result;
}

void main(){
	vec3 result;

	result += calculatorSpotLight(spotLight01);
	result += calculatorSpotLight(spotLight02);
	result += calculatorDirectionalLight(directionalLight01);
	result += calculatorPointLight(pointLight01);
	result += calculatorPointLight(pointLight02);
	result += calculatorPointLight(pointLight03);
	result += calculatorPointLight(pointLight04);
	FragColor = vec4(result,1.0f);
	
	vec3 emission = texture(material.emission,aTexCoord).xyz;

	//--------------------点光源计算-----------------------------------------
	//float dist = length(pointLight.position - fragPos);
	//float attenuation = 1.0f / (pointLight.constant + pointLight.linear * dist + pointLight.quadratic * (dist * dist));

	emission = emission * ((sin(time) * 0.5) + 0.5);
	emission = vec3(0.0f);

	//FragColor = vec4(((ambine + diffuse + specular) * attenuation + emission)  ,1.0f);
}