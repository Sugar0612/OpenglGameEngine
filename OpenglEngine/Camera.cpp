#include "Camera.h"

Camera::Camera(glm::vec3 postion, glm::vec3 target, glm::vec3 worldup): Postion(postion), WorldUp(worldup)
{
	Forward = glm::normalize(target - Postion);
	Right = glm::normalize(glm::cross(WorldUp, Forward));
	Up = glm::normalize(glm::cross(Right, Forward));
}

Camera::Camera(glm::vec3 postion, float pitch, float yaw, glm::vec3 wordlup): Postion(postion), WorldUp(wordlup)
{
	pitch = glm::radians(pitch);
	yaw = glm::radians(yaw);
	Forward.x = glm::cos(pitch) * glm::sin(yaw);
	Forward.y = glm::sin(pitch);
	Forward.z = glm::cos(pitch) * glm::cos(yaw);
	Right = glm::normalize(glm::cross(WorldUp, Forward));
	Up = glm::normalize(glm::cross(Right, Forward));
}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(Postion, Postion + Forward, WorldUp);
}

Camera::~Camera()
{
}


