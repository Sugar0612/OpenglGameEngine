#pragma once
#include "glm/glm.hpp"
#include <glm/gtx/rotate_vector.hpp>

class LightPoint
{
public:
	LightPoint(glm::vec3 _position, glm::vec3 _color, glm::vec3 _angles);
	~LightPoint();

	glm::vec3 position;
	glm::vec3 color = glm::vec3(1.f, 1.f, 1.f);
	glm::vec3 angles;
	glm::vec3 direction = glm::vec3(0.f, 0.f, 1.0f);

	float constant;
	float linear;
	float quadratic;
};

