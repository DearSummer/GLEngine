#pragma once
#include <glm/vec3.hpp>

struct SpotLight
{
	glm::vec3 position;
	glm::vec3 direction;

	float cutOff;
	float outerCutOff;

	glm::vec3 ambine;
	glm::vec3 diffuse;
	glm::vec3 specular;
};
