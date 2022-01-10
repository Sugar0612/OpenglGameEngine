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

	float multiple = 0.005f;

	float speedX = 0.f;
	float speedY = 0.f;
	float speedZ = 0.f;

	float Pitch;
	float Yaw;
public:
	glm::mat4 GetViewMatrix();

	void CameraMovment(float dirX, float dirY);

	void UpdataCameraPos();
private:
	void UpdataCameraVector();
};

