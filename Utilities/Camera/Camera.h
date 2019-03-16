#ifndef COMP_371_A3_CAMERA_H
#define COMP_371_A3_CAMERA_H
#include "glm.hpp"
#include "../../GLM/glm/gtc/matrix_transform.hpp"
#include "../Shading/Shader.h"
#include "../ErrorHandling/ErrorHandlingFunctions.h"
#include "../../Loaders/ObjectLoader.h"

class Camera
{
    private:
        glm::vec3 camera_position;
        glm::vec3 camera_direction;
        glm::vec3 right_axis;
        glm::vec3 up_axis;
        glm::mat4 Projection;
        glm::mat4 Model;
        float camera_speed;
        Shader* shader;
        glm::mat4 compute_view();
        const char* file_path;
        bool load();
        std::vector<int> indices;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> uvs;
        GLuint VAO;
        GLuint vertex_buffer;
        GLuint normal_buffer;
        GLuint texture_buffer;
        GLuint EBO;
        GLuint mesh_type;

    public:
        Camera(const char* filepath);
        ~Camera();
        inline glm::vec3 getPosition(){return camera_position;}
        inline glm::vec3 getDirection(){return camera_direction;}
        inline glm::vec3 getRightAxis(){return right_axis;}
        inline glm::vec3 getUpAxis(){return up_axis;}
        inline float getSpeed(){return camera_speed;}
        inline void setSpeed(float s){camera_speed = s;}
        inline void setPosition(glm::vec3 p){camera_position = p;}
        inline void setDirection(glm::vec3 d){camera_direction = d;}
        inline void setRightAxis(glm::vec3 r){right_axis = r;}
        inline void setUpAxis(glm::vec3 up){up_axis = up;}
        inline void setShader(Shader* s){shader = s;}
        glm::mat4 getView();
        void Render();
        void move_forward();
        inline glm::mat4 getProjection(){return Projection;}
        inline glm::mat4 getModel(){return Model;}
        void setProjection(float fov_degrees, int window_width, int window_height, float near_plane, float far_plane);
};

#endif
