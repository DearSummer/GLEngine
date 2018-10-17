#pragma once
#include <glm/vec3.hpp>

struct PointLight
{
	glm::vec3 position;

	glm::vec3 ambine;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float constant;
	float linear;
	float quadratic;
};
