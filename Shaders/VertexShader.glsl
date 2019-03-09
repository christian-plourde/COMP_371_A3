#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 normals;

//the three color channels
uniform float red_channel;
uniform float green_channel;
uniform float blue_channel;

//information required for lighting
uniform vec3 light_color_1;
uniform vec3 light_color_2;
uniform vec3 light_color_3;
uniform vec3 light_color_4;
uniform vec3 light_position_1;
uniform vec3 light_position_2;
uniform vec3 light_position_3;
uniform vec3 light_position_4;
uniform vec3 view_position;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform int normal_as_color;
uniform int gouraudUsed;

out vec3 fragment_position;
out vec3 normal;
out vec3 vertex_color;

void main()
{
    //this is the code for gouraud
    if(gouraudUsed == 1)
    {
        normal = mat3(model_matrix)*normals;
        fragment_position = mat3(model_matrix)*vertexPosition_modelspace;
        gl_Position = projection_matrix*view_matrix*model_matrix*vec4(vertexPosition_modelspace, 1);

        //Ambient light
        float ambient_strength = 0.25f;
        vec3 ambient = ambient_strength * light_color_1 + ambient_strength*light_color_2 + ambient_strength*light_color_3 + ambient_strength*light_color_4;

        //diffuse light
        float diffuse_coeff = 0.75f;
        vec3 light_direction_1 = normalize(light_position_1 - vertexPosition_modelspace);
        vec3 light_direction_2 = normalize(light_position_2 - vertexPosition_modelspace);
        vec3 light_direction_3 = normalize(light_position_3 - vertexPosition_modelspace);
        vec3 light_direction_4 = normalize(light_position_4 - vertexPosition_modelspace);
        float diffuse_strength_1 = max(dot(normalize(normal), light_direction_1), 0.0f);
        float diffuse_strength_2 = max(dot(normalize(normal), light_direction_2), 0.0f);
        float diffuse_strength_3 = max(dot(normalize(normal), light_direction_3), 0.0f);
        float diffuse_strength_4 = max(dot(normalize(normal), light_direction_4), 0.0f);
        vec3 diffuse = diffuse_strength_1*diffuse_coeff*light_color_1 + diffuse_strength_2*diffuse_coeff*light_color_2 + diffuse_strength_3*diffuse_coeff*light_color_3 + diffuse_strength_4*diffuse_coeff*light_color_4;

        //specular light
        float spec_coeff = 1.0f;
        vec3 view_direction = normalize(view_position - vertexPosition_modelspace);
        vec3 reflect_light_direction_1 = reflect(-light_direction_1, normalize(normal));
        vec3 reflect_light_direction_2 = reflect(-light_direction_2, normalize(normal));
        vec3 reflect_light_direction_3 = reflect(-light_direction_3, normalize(normal));
        vec3 reflect_light_direction_4 = reflect(-light_direction_4, normalize(normal));
        float specular_strength_1 = pow(max(dot(reflect_light_direction_1, view_direction), 0.0f), 32);
        float specular_strength_2 = pow(max(dot(reflect_light_direction_2, view_direction), 0.0f), 32);
        float specular_strength_3 = pow(max(dot(reflect_light_direction_3, view_direction), 0.0f), 32);
        float specular_strength_4 = pow(max(dot(reflect_light_direction_4, view_direction), 0.0f), 32);
        vec3 specular = specular_strength_1*spec_coeff*light_color_1 + specular_strength_2*spec_coeff*light_color_2 + specular_strength_3*spec_coeff*light_color_3 + specular_strength_4*spec_coeff*light_color_4;

        if(normal_as_color == 1)
        {
            vertex_color = (specular + ambient + diffuse)*normal;
        }

        else
        {
            vertex_color = (specular + ambient + diffuse)*vec3(red_channel, green_channel, blue_channel);
        }
    }

    else
    {
        normal = mat3(model_matrix)*normals;
        fragment_position = mat3(model_matrix)*vertexPosition_modelspace;

        gl_Position = projection_matrix*view_matrix*model_matrix*vec4(vertexPosition_modelspace, 1);
    }
}