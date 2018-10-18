#pragma once
#include "Shader.h"
#include "Light/PointLight.h"
#include "Light/DirectionalLight.h"
#include "Light/SpotLight.h"

#include <glm/vec3.hpp>

enum LightType
{
	POINT_LIGHT,
	DIRECTIONAL_LIGHT,
	SPOT_LIGHT
};

class Light
{
	Shader* shader;
	LightType type = DIRECTIONAL_LIGHT;

	DirectionalLight directionalLight;
	PointLight pointLight;
	SpotLight spotLight;

	Light(Shader* shader);
public:

	void active(const std::string& name);
	glm::vec3 getPosition() const;
	glm::vec3 getLightColor() const;
	~Light();

	class Builder
	{
		Shader* shader;
		glm::vec3 ambine;
		glm::vec3 diffuse;
		glm::vec3 specular;

		DirectionalLight directionalLight;
		PointLight pointLight;
		SpotLight spotLight;

		LightType type = DIRECTIONAL_LIGHT;
	public:
		Builder(Shader* shader,glm::vec3 ambine,glm::vec3 diffuse,glm::vec3 specular);
		Builder& setLightType(LightType type);
		Builder& setDirectionalLight(glm::vec3 directional);
		Builder& setPointLight(glm::vec3 position,float constant,float linear,float quadratic);
		Builder& setSpotLight(glm::vec3 position, glm::vec3 directional, float cutOff,float outerCutOff);
		Light* Build() const;
	};
};

