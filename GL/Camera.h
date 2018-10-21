#pragma once

#define CAMERA_FORWARD_DIRECTION glm::vec3(0,0,1)
#define CAMERA_UP_DIRECTION glm::vec3(0,1,0)
#define CAMERA_RIGHT_DIRECTION glm::vec3(1,0,0)

#define ZERO_VECTOR3 glm::vec3(0,0,0)
#include <glm/ext/quaternion_float.hpp>

class Camera
{
private:

	glm::vec3 position;
	glm::quat orientation;

	glm::vec3 worldUp = glm::vec3(0, 1, 0);

public:

	glm::vec3 forward = CAMERA_FORWARD_DIRECTION;
	glm::vec3 up = CAMERA_UP_DIRECTION;
	glm::vec3 right = CAMERA_RIGHT_DIRECTION;

	Camera(const Camera&) = default;
	explicit Camera(const glm::vec3 &position);
	Camera(const glm::vec3 &position, const glm::quat &orientation);

	~Camera() = default;

	Camera& operator=(const Camera&) = default;

	glm::mat4 getViewMatrix() const;

	glm::vec3 &getPosition();
	glm::quat &getOrientation();


	void rotate(float angle,const glm::vec3 &axis);
	void rotate(float angle, float x, float y, float z);

	void translate(const glm::vec3 &v);
	void translate(float x, float y, float z);

	void yaw(float angle);
	void pitch(float angle);
	void roll(float angle);

};

