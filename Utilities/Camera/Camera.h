#ifndef COMP_371_A3_CAMERA_H
#define COMP_371_A3_CAMERA_H
#include "glm.hpp"
#include "../../GLM/glm/gtc/matrix_transform.hpp"

class Camera
{
    private:
        glm::vec3 camera_position;
        glm::vec3 camera_direction;
        glm::vec3 right_axis;
        glm::vec3 up_axis;
        float camera_speed;


    public:
        Camera();
        Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 right, glm::vec3 up);
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

};

#endif
