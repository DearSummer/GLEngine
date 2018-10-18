#include "Light.h"



Light::Light(Shader* shader):
	shader(shader)
{
}


void Light::active(const std::string & name)
{

	switch (type)
	{
	case POINT_LIGHT:
		shader->setVector3(name + ".ambine", pointLight.ambine.x, pointLight.ambine.y, pointLight.ambine.z);
		shader->setVector3(name + ".position", pointLight.position.x, pointLight.position.y, pointLight.position.z);
		shader->setVector3(name + ".diffuse", pointLight.diffuse.x, pointLight.diffuse.y, pointLight.diffuse.z);
		shader->setVector3(name + ".specular", pointLight.specular.x, pointLight.specular.y, pointLight.specular.z);
		shader->setFloat(name + ".constant", pointLight.constant);
		shader->setFloat(name + ".linear", pointLight.linear);
		shader->setFloat(name + ".quadratic", pointLight.quadratic);
		break;
	case DIRECTIONAL_LIGHT:
		shader->setVector3(name + ".direction", directionalLight.directional.x, directionalLight.directional.y, directionalLight.directional.z);
		shader->setVector3(name + ".ambine", directionalLight.ambine.x, directionalLight.ambine.y, directionalLight.ambine.z);
		shader->setVector3(name + ".diffuse", directionalLight.diffuse.x, directionalLight.diffuse.y, directionalLight.diffuse.z);
		shader->setVector3(name + ".specular", directionalLight.specular.x, directionalLight.specular.y, directionalLight.specular.z);
		break;
	case SPOT_LIGHT:
		shader->setVector3(name + ".ambine", spotLight.ambine.x, spotLight.ambine.y, spotLight.ambine.z);
		shader->setVector3(name + ".diffuse", spotLight.diffuse.x, spotLight.diffuse.y, spotLight.diffuse.z);
		shader->setVector3(name + ".specular", spotLight.specular.x, spotLight.specular.y, spotLight.specular.z);
		shader->setVector3(name + ".position", spotLight.position.x, spotLight.position.y, spotLight.position.z);
		shader->setVector3(name + ".direction", spotLight.direction.x, spotLight.direction.y, spotLight.direction.z);
		shader->setFloat(name + ".cutOff", spotLight.cutOff);
		shader->setFloat(name + ".outerCutOff", spotLight.outerCutOff);
		break;
	}
}

glm::vec3 Light::getPosition() const
{
	glm::vec3 result(0, 0, 0);
	switch (type)
	{
	case POINT_LIGHT:
		result = pointLight.position;
		break;
	case SPOT_LIGHT:
		result = spotLight.position;
		break;
	default: 
		break;
	}
	return result;
}

glm::vec3 Light::getLightColor() const
{
	glm::vec3 result(0);
	switch (type)
	{
	case POINT_LIGHT:
		result = pointLight.ambine;
		break;
	case DIRECTIONAL_LIGHT:
		result = directionalLight.ambine;
		break;
	case SPOT_LIGHT:
		result = spotLight.ambine;
		break;
		default: break;

	}
	return result;
}

Light::~Light() = default;

Light::Builder::Builder(Shader* shader, const glm::vec3 ambine, const glm::vec3 diffuse, const glm::vec3 specular)
	: shader(shader), ambine(ambine), diffuse(diffuse), specular(specular)
{
	directionalLight.ambine = ambine;
	directionalLight.diffuse = diffuse;
	directionalLight.specular = specular;

	pointLight.ambine = ambine;
	pointLight.diffuse = diffuse;
	pointLight.specular = specular;

	spotLight.ambine = ambine;
	spotLight.diffuse = diffuse;
	spotLight.specular = specular;
}

Light::Builder& Light::Builder::setLightType(LightType type)
{
	// TODO: insert return statement here
	this->type = type;
	return *this;
}

Light::Builder& Light::Builder::setDirectionalLight(glm::vec3 directional)
{
	// TODO: insert return statement here
	directionalLight.directional = directional;
	directionalLight.ambine = ambine;
	directionalLight.diffuse = diffuse;
	directionalLight.specular = specular;

	setLightType(DIRECTIONAL_LIGHT);
	return *this;
}

Light::Builder& Light::Builder::setPointLight(glm::vec3 position, float constant, float linear, float quadratic)
{
	// TODO: insert return statement here
	pointLight.position = position;
	pointLight.constant = constant;
	pointLight.quadratic = quadratic;
	pointLight.linear = linear;

	setLightType(POINT_LIGHT);
	return *this;
}

Light::Builder& Light::Builder::setSpotLight(const glm::vec3 position,
											 const glm::vec3 directional, 
											 const float cutOff, 
											 const float outerCutOff)
{
	spotLight.position = position;
	spotLight.cutOff = cutOff;
	spotLight.outerCutOff = outerCutOff;
	spotLight.direction = directional;

	setLightType(SPOT_LIGHT);
	return *this;
}

Light * Light::Builder::Build() const
{
	// TODO: insert return statement here
	Light * light = new Light(shader);
	light->pointLight = pointLight;
	light->spotLight = spotLight;
	light->directionalLight = directionalLight;
	light->type = type;
	return light;
}
