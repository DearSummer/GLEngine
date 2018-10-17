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
//uniform DirectionalLight light;
//uniform PointLight pointLight;
uniform SpotLight spotLight;

uniform vec3 ambineColor;
uniform vec3 lightColor;

uniform vec3 lightPos;

uniform vec3 cameraPos;

uniform float time;

out vec4 FragColor;

void main(){
	vec3 lightDir = normalize(spotLight.position - fragPos);
	

	//vec3 lightDir = normalize(-spotLight.direction);
	vec3 reflectVec = reflect(-lightDir,objNormalize);

	vec3 cameraVec = normalize(cameraPos - fragPos);

	float specularAmount = pow(max(dot(reflectVec,cameraVec),0),material.shininess);

	float theta = dot(lightDir,normalize(-spotLight.direction));
	float epsilon = spotLight.cutOff - spotLight.outerCutOff;
	float intensity = clamp((theta - spotLight.outerCutOff) / epsilon , 0.0f,1.0f);

	vec3 diffuse = texture(material.diffuse,aTexCoord).xyz  * max(dot(lightDir,objNormalize),0) * spotLight.diffuse * intensity;
	vec3 specular = texture(material.specular,aTexCoord).xyz * specularAmount * spotLight.specular * intensity;	
	vec3 ambine = spotLight.ambine * texture(material.diffuse,aTexCoord).xyz;

	FragColor = vec4((ambine + diffuse + specular)  ,1.0f);

	
	vec3 emission = texture(material.emission,aTexCoord).xyz;

	//--------------------点光源计算-----------------------------------------
	//float dist = length(pointLight.position - fragPos);
	//float attenuation = 1.0f / (pointLight.constant + pointLight.linear * dist + pointLight.quadratic * (dist * dist));

	emission = emission * ((sin(time) * 0.5) + 0.5);
	emission = vec3(0.0f);

	//FragColor = vec4(((ambine + diffuse + specular) * attenuation + emission)  ,1.0f);
}