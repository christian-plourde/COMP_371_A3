#include "DepthMapLight.h"

DepthMapLight::DepthMapLight()
{
    near_plane = 1.0f;
    far_plane = 7.5f;
    top = 100.0f;
    bottom = -100.0f;
    right = 100.0f;
    left = -100.0f;
    projection = glm::ortho(left, right, bottom, top, near_plane, far_plane);
    eye = glm::vec3(0, 20, 10);
    looking_at = glm::vec3(0,0,0);
    up_vector = glm::vec3(0,1,0);
    view = glm::lookAt(eye, looking_at, up_vector);
    model = glm::mat4(1.0);
    light_matrix = projection*view*model;
}

DepthMapLight::~DepthMapLight() {}

