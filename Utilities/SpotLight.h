#ifndef COMP_371_A3_SPOTLIGHT_H
#define COMP_371_A3_SPOTLIGHT_H

#include "glm.hpp"

class SpotLight
{
    private:
        glm::vec3 spot_position;
        glm::vec3 spot_direction;
        float cutoff_angle;
    public:
        SpotLight();
        ~SpotLight();
        inline void setPosition(glm::vec3 pos){spot_position = pos;}
        inline void setDirection(glm::vec3 dir){spot_direction = dir;}
        inline void setCutoffAngle(float angle){cutoff_angle = angle;}
        void setPosition(float x, float y, float z);
        void setDirection(float x, float y, float z);

};

#endif
