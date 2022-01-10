#include "Camera.h"

Camera::Camera(glm::vec3 postion, glm::vec3 target, glm::vec3 worldup): Postion(postion), WorldUp(worldup)
{
	Forward = glm::normalize(target - Postion);
	Right = glm::normalize(glm::cross(WorldUp, Forward));
	Up = glm::normalize(glm::cross(Right, Forward));
}

Camera::Camera(glm::vec3 postion, float pitch, float yaw, glm::vec3 wordlup): Postion(postion), WorldUp(wordlup)
{
	Pitch = glm::radians(pitch);
	Yaw = glm::radians(yaw);
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(WorldUp, Forward));
	Up = glm::normalize(glm::cross(Right, Forward));
}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(Postion, Postion + Forward, WorldUp);
}


void Camera::UpdataCameraVector() {
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(WorldUp, Forward));
	Up = glm::normalize(glm::cross(Right, Forward));
}

void Camera::CameraMovment(float dirX, float dirY) {
	Pitch -= (dirY * multiple);
	Yaw -= (dirX * multiple);
	UpdataCameraVector();
}

void Camera::UpdataCameraPos()
{
	Postion += Forward * speedZ;
	Postion += Right * speedX;
	Postion += WorldUp * speedY;

	speedX = 0.f;
	speedY = 0.f;
	speedZ = 0.f;
}

Camera::~Camera()
{
}


