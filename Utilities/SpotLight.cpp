#include "SpotLight.h"

SpotLight::SpotLight()
{

}

SpotLight::~SpotLight() {}

void SpotLight::setPosition(float x, float y, float z)
{
    spot_position = glm::vec3(x, y, z);
}

void SpotLight::setDirection(float x, float y, float z)
{
    spot_direction = glm::vec3(x, y, z);
}