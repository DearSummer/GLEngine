#include "Camera.h"




void Camera::updateCameraVertor()
{
	forward.x = glm::cos(pitch) * glm::sin(yaw);
	forward.y = glm::sin(pitch);
	forward.z = glm::cos(pitch) * glm::cos(yaw);

	right = glm::normalize(glm::cross(forward, worldUpCoordinate));
	up = glm::normalize(glm::cross(forward, right));
}

Camera::Camera(const glm::vec3 position, const glm::vec3 lookAtTargetPos, const glm::vec3 worldUpCoordinate)
{
	this->position = position;
	this->worldUpCoordinate = worldUpCoordinate;

	forward = glm::normalize(lookAtTargetPos - position);
	right = glm::normalize(glm::cross(forward, worldUpCoordinate));
	up = glm::normalize(glm::cross(forward, right));
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUpCoordinate)
{
	this->position = position;
	this->worldUpCoordinate = worldUpCoordinate;

	this->pitch = pitch;
	this->yaw = yaw;

	forward.x = glm::cos(pitch) * glm::sin(yaw);
	forward.y = glm::sin(pitch);
	forward.z = glm::cos(pitch) * glm::cos(yaw);

	right = glm::normalize(glm::cross(forward, worldUpCoordinate));
	up = glm::normalize(glm::cross(forward, right));
}

Camera::~Camera()
= default;

glm::mat4 Camera::getViewMatix() const
{
	return glm::lookAt(position, position + forward, worldUpCoordinate);
}

void Camera::updatePos(const glm::vec3 deltaPos)
{
	this->position += deltaPos;
}

void Camera::updateLookAt(const float detlaPitch, const float deplaYaw)
{
	pitch += detlaPitch;
	yaw += deplaYaw;

	updateCameraVertor();
}
