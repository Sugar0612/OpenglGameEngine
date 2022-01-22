#include "LightPoint.h"

LightPoint::LightPoint(glm::vec3 _position, glm::vec3 _color, glm::vec3 _angles):
	position(_position), color(_color), angles(_angles)
{
	constant = 1.f;
	linear = 0.09f;
	quadratic = 0.032f;
}

LightPoint::~LightPoint()
{
}
