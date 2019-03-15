#include "SpotLight.h"

SpotLight::SpotLight()
{
    spot_position = glm::vec3(0,20,10);
    spot_direction = glm::vec3(0,0,0);
    spot_color = glm::vec3(1,1,1);
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

void SpotLight::setColor(float x, float y, float z)
{
    spot_color = glm::vec3(x, y, z);
}

float SpotLight::getCutoffCosine()
{
    //this is to compare in the fragment shader since we will be doing the dot product to get the light direction
    return glm::cos(glm::radians(cutoff_angle));
}