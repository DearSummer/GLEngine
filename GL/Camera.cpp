#include "Camera.h"
#include <glm/gtc/quaternion.inl>
#include <glm/ext/quaternion_trigonometric.inl>
#include <iostream>
#include <valarray>



Camera::Camera(const glm::vec3 & position):position(position),orientation(glm::quat_cast(glm::mat4(1.0f)))
{	
}

Camera::Camera(const glm::vec3 & position, const glm::quat & orientation)
	:position(position),orientation(orientation)
{
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::translate(glm::mat4_cast(orientation), position);
}

glm::vec3 & Camera::getPosition()
{
	// TODO: insert return statement here
	return position;
}

glm::quat & Camera::getOrientation()
{
	// TODO: insert return statement here
	return orientation;
}

std::string Camera::toString() const
{
	std::string posDes = "Camera Pos";
	posDes.append(" X : " + std::to_string(position.x));
	posDes.append(" Y : " + std::to_string(position.y));
	posDes.append(" Z : " + std::to_string(position.z));
	return posDes;
	
}

void Camera::rotate(const float angle, const glm::vec3 & axis)
{
	orientation *= glm::angleAxis(angle, glm::normalize(axis * orientation));
}

void Camera::rotate(const float angle, const float x, const float y, const float z)
{
	orientation *= glm::angleAxis(angle, glm::normalize(glm::vec3(x, y, z) * orientation));
}

void Camera::translate(const glm::vec3 & v)
{
	position += v * orientation;
}

void Camera::translate(const float x, const float y, const float z)
{
	position += glm::vec3(x, y, z) * orientation;
}

void Camera::yaw(const float angle)
{
	rotate(angle, 0.0f, 1.0f, 0.0f);
}

void Camera::pitch(const float angle)
{
	rotate(angle, 1.0f, 0.0f, 0.0f);
}

void Camera::roll(const float angle)
{
	rotate(angle, 0.0f, 0.0f, 1.0f);
}
