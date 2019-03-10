#version 330 core

layout (location = 0) in vec3 vertexPosition_modelspace;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 textures;

//output variables
out vec3 fragment_position;
out vec3 normal;
out vec2 tex_coords;
out vec4 frag_pos_light_space;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform mat4 light_matrix;

void main()
{
    fragment_position = vec3(model_matrix*vec4(vertexPosition_modelspace, 1));
    normal = transpose(inverse(mat3(model_matrix)))*normals;
    tex_coords = textures;
    frag_pos_light_space = light_matrix*vec4(fragment_position, 1);
    gl_Position = projection_matrix*view_matrix*model_matrix*vec4(vertexPosition_modelspace, 1);
}

