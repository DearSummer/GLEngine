#version 330 core

in vec3 fragPos;
in vec3 objNormalize;
in vec2 aTexCoord;

struct Material{

	sampler2D texture_diffuse_1;
	sampler2D texture_diffuse_2;
	sampler2D texture_diffuse_3;
	sampler2D texture_specular_1;
	sampler2D texture_specular_2;
	sampler2D texture_specular_3;
	sampler2D texture_emissive_1;
	sampler2D texture_emissive_2;
	sampler2D texture_normal_1;
	sampler2D texture_normal_2;
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

	vec3 diffuse = texture(material.texture_diffuse_1,aTexCoord).xyz  * max(dot(lightDir,objNormalize),0) * light.diffuse * intensity;
	diffuse += texture(material.texture_diffuse_2,aTexCoord).xyz  * max(dot(lightDir,objNormalize),0) * light.diffuse * intensity;
	diffuse += texture(material.texture_diffuse_3,aTexCoord).xyz  * max(dot(lightDir,objNormalize),0) * light.diffuse * intensity;
	vec3 specular = texture(material.texture_specular_1,aTexCoord).xyz * specularAmount * light.specular * intensity;	
	specular += texture(material.texture_specular_1,aTexCoord).xyz * specularAmount * light.specular * intensity;	
	specular += texture(material.texture_specular_1,aTexCoord).xyz * specularAmount * light.specular * intensity;	
	vec3 ambine = light.ambine * texture(material.texture_diffuse_1,aTexCoord).xyz;
	ambine += light.ambine * texture(material.texture_diffuse_2,aTexCoord).xyz;
	ambine += light.ambine * texture(material.texture_diffuse_3,aTexCoord).xyz;

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


	vec3 diffuse = texture(material.texture_diffuse_1,aTexCoord).xyz  * max(dot(lightDir,objNormalize),0) * light.diffuse;
	diffuse += texture(material.texture_diffuse_2,aTexCoord).xyz  * max(dot(lightDir,objNormalize),0) * light.diffuse;
	diffuse += texture(material.texture_diffuse_3,aTexCoord).xyz  * max(dot(lightDir,objNormalize),0) * light.diffuse;

	vec3 specular = texture(material.texture_specular_1,aTexCoord).xyz * specularAmount * light.specular;	
	specular = texture(material.texture_specular_2,aTexCoord).xyz * specularAmount * light.specular;	
	specular = texture(material.texture_specular_3,aTexCoord).xyz * specularAmount * light.specular;	

	vec3 ambine = light.ambine * texture(material.texture_diffuse_1,aTexCoord).xyz;
	ambine = light.ambine * texture(material.texture_diffuse_2,aTexCoord).xyz;
	ambine = light.ambine * texture(material.texture_diffuse_3,aTexCoord).xyz;

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

	
	vec3 diffuse = texture(material.texture_diffuse_1,aTexCoord).xyz  * max(dot(lightDir,objNormalize),0) * light.diffuse * attenuation;
	diffuse += texture(material.texture_diffuse_2,aTexCoord).xyz  * max(dot(lightDir,objNormalize),0) * light.diffuse * attenuation;
	diffuse += texture(material.texture_diffuse_3,aTexCoord).xyz  * max(dot(lightDir,objNormalize),0) * light.diffuse * attenuation;

	vec3 specular = texture(material.texture_specular_1,aTexCoord).xyz * specularAmount * light.specular * attenuation;	
	specular += texture(material.texture_specular_2,aTexCoord).xyz * specularAmount * light.specular * attenuation;	
	specular += texture(material.texture_specular_3,aTexCoord).xyz * specularAmount * light.specular * attenuation;	

	vec3 ambine = light.ambine * texture(material.texture_diffuse_1,aTexCoord).xyz * attenuation;
	ambine += light.ambine * texture(material.texture_diffuse_2,aTexCoord).xyz * attenuation;
	ambine += light.ambine * texture(material.texture_diffuse_3,aTexCoord).xyz * attenuation;

	result += diffuse;
	result += specular;
	result += ambine;

	return result;
}

void main(){
	vec3 result;

	result += calculatorSpotLight(spotLight01);
	//result += calculatorSpotLight(spotLight02);
	//result += calculatorDirectionalLight(directionalLight01);
	//result += calculatorPointLight(pointLight01);
	//result += calculatorPointLight(pointLight02);
	//result += calculatorPointLight(pointLight03);
	//result += calculatorPointLight(pointLight04);
	
	//result += texture(material.texture_emissive_1,aTexCoord).xyz;
	//result += texture(material.texture_emissive_2,aTexCoord).xyz;

	FragColor = vec4(result,1.0f);

}