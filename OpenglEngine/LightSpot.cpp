#include "LightSpot.h"

LightSpot::LightSpot(glm::vec3 _position, glm::vec3 _color, glm::vec3 _angles):
	position(_position), color(_color), angles(_angles)
{
	UpdateDirection();
}


void LightSpot::UpdateDirection()
{
	direction = glm::vec3(0.f, 0.f, 1.f);
	direction = glm::rotateZ(direction, angles.z);
	direction = glm::rotateX(direction, angles.x);
	direction = glm::rotateY(direction, angles.y);

	direction = -1.f * direction;
}


LightSpot::~LightSpot()
{
}