#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 light_matrix;

void main()
{
    gl_Position = light_matrix*vec4(vertexPosition_modelspace, 1);
}
