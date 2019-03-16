#include "Camera.h"

Camera::~Camera()
{
    delete shader;
}

Camera::Camera(const char* filepath)
{
    file_path = filepath;
    GLCall(glGenVertexArrays(1, &VAO));
    GLCall(glBindVertexArray(VAO));
    mesh_type = GL_TRIANGLES;
    camera_position = glm::vec3(0,0,3);
    glm::vec3 camera_target = glm::vec3(0,0,0); //point the camera to the origin of the world
    camera_direction = glm::normalize(camera_position - camera_target);
    glm::vec3 up = glm::vec3(0,1,0);
    right_axis = glm::normalize(glm::cross(up, camera_direction));
    up_axis = glm::cross(camera_direction, right_axis);
    Model = glm::mat4(1.0f);
    camera_speed = 0.1;
}

glm::mat4 Camera::compute_view()
{
    return glm::lookAt(camera_position, camera_position + camera_direction, up_axis);
}

glm::mat4 Camera::getView()
{
    return compute_view();
}

void Camera::move_forward()
{
    camera_position += camera_speed*camera_direction;
}

void Camera::setProjection(float fov_degrees, int window_width, int window_height, float near_plane, float far_plane)
{
    Projection = glm::perspective(glm::radians(fov_degrees), (float)window_width/window_height, near_plane, far_plane);
}

void Camera::Render()
{
    shader -> use();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

bool Camera::load()
{
    //function to load an object into the class
    if(!LoadOBJ(file_path, indices, vertices, normals, uvs))
        return false;

    //once we have loaded the data from the file, we should set the data in our buffers

    //next we will need a buffer for the vertices, normals, and uvs
    GLCall(glGenBuffers(1, &vertex_buffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertices.size(), &vertices.front(), GL_STATIC_DRAW));

    GLCall(glGenBuffers(1, &normal_buffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, normal_buffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*normals.size(), &normals.front(), GL_STATIC_DRAW));

    GLCall(glGenBuffers(1, &texture_buffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, texture_buffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*uvs.size(), &uvs.front(), GL_STATIC_DRAW));

    //finally we need an EBO for the indices
    GLCall(glGenBuffers(1, &EBO));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indices.size(), &indices.front(), GL_STATIC_DRAW));
    return true;
}

