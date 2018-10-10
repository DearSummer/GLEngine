#include "Camera.h"


void Camera::updateCameraVertor()
{

	forward.x = glm::cos(pitch) * glm::sin(yaw);
	forward.y = glm::sin(pitch);
	forward.z = glm::cos(pitch) * glm::cos(yaw);

	right = glm::normalize(glm::cross(forward, worldUpCoordinate));
	up = glm::normalize(glm::cross(right, forward));
}

glm::mat4 Camera::lookAtMatrix() const
{
	const glm::vec3 zAxis = glm::normalize(-forward);
	const glm::vec3 xAxis = glm::normalize(glm::cross(worldUpCoordinate, zAxis));
	const glm::vec3 yAxis = glm::normalize(glm::cross(zAxis, xAxis));

	glm::mat4 translationMat(1.0f);
	translationMat[3][0] = -position.x;
	translationMat[3][1] = -position.y;
	translationMat[3][2] = -position.z;

	glm::mat4 rotationMat(1.0f);
	rotationMat[0][0] = xAxis.x;
	rotationMat[1][0] = xAxis.y;
	rotationMat[2][0] = xAxis.z;
	
	rotationMat[0][1] = yAxis.x;
	rotationMat[1][1] = yAxis.y;
	rotationMat[2][1] = yAxis.z;

	rotationMat[0][2] = zAxis.x;
	rotationMat[1][2] = zAxis.y;
	rotationMat[2][2] = zAxis.z;

	return rotationMat * translationMat;
}

Camera::Camera(const glm::vec3 position, const glm::vec3 lookAtTargetPos, const glm::vec3 worldUpCoordinate)
{
	this->position = position;
	this->worldUpCoordinate = worldUpCoordinate;

	forward = glm::normalize(lookAtTargetPos - position);
	right = glm::normalize(glm::cross(forward, worldUpCoordinate));
	up = glm::normalize(glm::cross(right, forward));

	pitch = glm::asin(forward.y);
	yaw = glm::acos(forward.z / glm::cos(pitch));
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUpCoordinate)
{
	this->position = position;
	this->worldUpCoordinate = worldUpCoordinate;

	this->pitch = pitch;
	this->yaw = yaw;

	updateCameraVertor();
}

Camera::~Camera()
= default;

glm::mat4 Camera::getViewMatrix() const
{
	//return glm::lookAt(position, position + forward, worldUpCoordinate);
	return lookAtMatrix();
}

void Camera::updatePos(const glm::vec3 deltaPos)
{
	this->position += deltaPos;

	updateCameraVertor();
}

void Camera::updateLookAt(const float detlaPitch, const float detlaYaw)
{
	pitch += detlaPitch;
	yaw += detlaYaw;

	updateCameraVertor();
}
