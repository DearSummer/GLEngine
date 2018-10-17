#pragma once
#include <glm/vec3.hpp>

struct DirectionalLight
{
	glm::vec3 directional;

	glm::vec3 ambine;
	glm::vec3 diffuse;
	glm::vec3 specular;

};
