#version 330 core

out vec3 color;

//the three color channels
uniform vec3 light_color_1;
uniform vec3 light_color_2;
uniform vec3 light_color_3;
uniform vec3 light_color_4;
uniform vec3 light_position_1;
uniform vec3 light_position_2;
uniform vec3 light_position_3;
uniform vec3 light_position_4;
uniform vec3 spot_light_1_position;
uniform vec3 spot_light_1_direction;
uniform vec3 spot_light_1_color;
uniform float spot_light_1_cutoff;

uniform vec3 view_position;
uniform sampler2D depth_tex;

in vec3 fragment_position;
in vec3 normal;
in vec2 tex;

void main()
{

        color = vec3(1,1,1);

        //we need to calculate the direction of the light to see if it is in the spot light
        vec3 spot_light_dir_1 = normalize(spot_light_1_position - fragment_position);
        vec3 spot_light_color_1 = spot_light_1_color;
        float theta = dot(spot_light_dir_1, normalize(-spot_light_1_direction));
        float spot_light_1_modifier = 1.0;

        if(theta < spot_light_1_cutoff)
            spot_light_1_modifier = 0.0;

        //Ambient light
        float ambient_strength = 0.25f;
        vec3 ambient = ambient_strength * light_color_1 + ambient_strength*light_color_2
        + ambient_strength*light_color_3 + ambient_strength*light_color_4
        + ambient_strength*spot_light_color_1;

        //diffuse light
        float diffuse_coeff = 0.75f;
        vec3 light_direction_1 = normalize(light_position_1 - fragment_position);
        vec3 light_direction_2 = normalize(light_position_2 - fragment_position);
        vec3 light_direction_3 = normalize(light_position_3 - fragment_position);
        vec3 light_direction_4 = normalize(light_position_4 - fragment_position);
        float diffuse_strength_1 = max(dot(normalize(normal), light_direction_1), 0.0f);
        float diffuse_strength_2 = max(dot(normalize(normal), light_direction_2), 0.0f);
        float diffuse_strength_3 = max(dot(normalize(normal), light_direction_3), 0.0f);
        float diffuse_strength_4 = max(dot(normalize(normal), light_direction_4), 0.0f);
        float spot_light_1_diffuse_strength = max(dot(normalize(normal), spot_light_dir_1), 0.0f);

        vec3 diffuse = diffuse_strength_1*diffuse_coeff*light_color_1 + diffuse_strength_2*diffuse_coeff*light_color_2
        + diffuse_strength_3*diffuse_coeff*light_color_3 + diffuse_strength_4*diffuse_coeff*light_color_4
        + spot_light_1_diffuse_strength*diffuse_coeff*spot_light_color_1*spot_light_1_modifier;

        //specular light
        float spec_coeff = 1.0f;
        vec3 view_direction = normalize(view_position - fragment_position);
        vec3 reflect_light_direction_1 = reflect(-light_direction_1, normalize(normal));
        vec3 reflect_light_direction_2 = reflect(-light_direction_2, normalize(normal));
        vec3 reflect_light_direction_3 = reflect(-light_direction_3, normalize(normal));
        vec3 reflect_light_direction_4 = reflect(-light_direction_4, normalize(normal));
        vec3 reflect_spot_light_direction_1 = reflect(-spot_light_dir_1, normalize(normal));
        float specular_strength_1 = pow(max(dot(reflect_light_direction_1, view_direction), 0.0f), 32);
        float specular_strength_2 = pow(max(dot(reflect_light_direction_2, view_direction), 0.0f), 32);
        float specular_strength_3 = pow(max(dot(reflect_light_direction_3, view_direction), 0.0f), 32);
        float specular_strength_4 = pow(max(dot(reflect_light_direction_4, view_direction), 0.0f), 32);
        float specular_strength_5 = pow(max(dot(reflect_spot_light_direction_1, view_direction), 0.0f), 32);
        vec3 specular = specular_strength_1*spec_coeff*light_color_1 + specular_strength_2*spec_coeff*light_color_2
        + specular_strength_3*spec_coeff*light_color_3 + specular_strength_4*spec_coeff*light_color_4
        + specular_strength_5*spec_coeff*spot_light_color_1*spot_light_1_modifier;

        color = (specular + ambient + diffuse)*color;
}