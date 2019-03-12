#include "MVP.h"
#include "../GLM/glm/gtc/matrix_transform.hpp"

MVP::MVP()
{
    Model = glm::mat4(1.0f);
    View = glm::lookAt(glm::vec3(0,0,-40),glm::vec3(0,0,0), glm::vec3(0, 1, 0));
    Projection = glm::mat4(1.0f);
}

MVP::~MVP()
{

}

void MVP::setModel(glm::mat4 model)
{
    Model = model;
}

void MVP::setView(glm::vec3 eye, glm::vec3 point, glm::vec3 up_vector)
{
    View = glm::lookAt(eye,point,up_vector);
}

void MVP::setView(glm::mat4 newView)
{
    View = newView;
}

void MVP::setProjection(float fov_degrees, int window_width, int window_height, float near_plane, float far_plane)
{
    Projection = glm::perspective(glm::radians(fov_degrees), (float)window_width/window_height, near_plane, far_plane);
}

