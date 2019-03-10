#version 330 core

out vec3 fragment_color;

in vec3 fragment_position;
in vec3 normal;
in vec2 tex_coords;
in vec4 frag_pos_light_space;

//uniform sampler2D diffuseTexture;
uniform sampler2D depthMap;

uniform vec3 light_position_1;
uniform vec3 view_position;

float Shadow()
{
    vec3 projection_coords = frag_pos_light_space.xyz / frag_pos_light_space.w;
    projection_coords = projection_coords*0.5 + 0.5;
    float closest_depth = texture(depthMap, projection_coords.xy).r;
    float current_depth = projection_coords.z;
    float shadow = current_depth > closest_depth ? 1.0 : 0.0;
    return shadow;
}

void main()
{
    vec3 color = vec3(0);
    vec3 normal_norm = normalize(normal);
    vec3 light_color = vec3(1.0);

    //ambient light
    vec3 ambient = color;

    //diffuse light
    vec3 light_direction = normalize(light_position_1 - fragment_position);
    float diffuse_strength = max(dot(light_direction, normal_norm), 0.0);
    vec3 diffuse = diffuse_strength*light_color;

    //specular light
    vec3 view_direction = normalize(view_position - fragment_position);
    float specular_strength = 0.0;
    vec3 halfway_direction = normalize(light_direction + view_direction);
    specular_strength = pow(max(dot(normal, halfway_direction), 0.0), 64);
    vec3 specular = specular_strength*light_color;
    float shadow = Shadow();
    vec3 lighting = (ambient + (1.0 - shadow)*(diffuse + specular))*color;
    fragment_color = vec3(lighting);
}