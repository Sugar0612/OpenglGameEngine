#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Camera
{
public:
	Camera(glm::vec3 postion, glm::vec3 target, glm::vec3 worldup);
	Camera(glm::vec3 postion, float pitch, float yaw, glm::vec3 wordlup);
	~Camera();

public:
	glm::vec3 Postion;
	glm::vec3 WorldUp;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;

	glm::mat4 view;

	float pitch;
	float yaw;
public:
	glm::mat4 GetViewMatrix();
};

