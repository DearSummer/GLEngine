#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define ZERO_VECTOR3 glm::vec3(0,0,0)

class Camera
{
private:
	glm::vec3 worldUpCoordinate = ZERO_VECTOR3;

	float pitch;
	float yaw;

	void updateCameraVertor();

public:
	Camera(glm::vec3 position, glm::vec3 lookAtTargetPos, glm::vec3 worldUpCoordinate = glm::vec3(0, 1, 0));
	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUpCoordinate = glm::vec3(0, 1, 0));
	~Camera();

	glm::mat4 getViewMatix() const;

	void updatePos(glm::vec3 deltaPos);
	void updateLookAt(float detlaPitch, float detlaYaw);

	glm::vec3 position = ZERO_VECTOR3;

	glm::vec3 up = ZERO_VECTOR3;
	glm::vec3 forward = ZERO_VECTOR3;
	glm::vec3 right = ZERO_VECTOR3;
};

