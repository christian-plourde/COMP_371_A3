#include "glm.hpp"
#include <iostream>

#ifndef COMP_371_A3_MVP
#define COMP_371_A3_MVP
//this class contains data for a model view projection matrix with perspective projection
class MVP
{
    private:
        glm::mat4 Model;
        glm::mat4 View;
        glm::mat4 Projection;

    public:
        MVP();
        ~MVP();
        void setModel(glm::mat4);
        void setView(glm::vec3, glm::vec3, glm::vec3);
        void setView(glm::mat4);
        void setProjection(float, int, int, float, float); //must be called after window has been initialized
        inline glm::mat4 getModel(){return Model;}
        inline glm::mat4 getView(){return View;}
        inline glm::mat4 getProjection(){return getProjection();}
};

#endif