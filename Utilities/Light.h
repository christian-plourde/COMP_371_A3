#include "glm.hpp"

class Light
{
    private:
        glm::vec3 position; //the position of the light
        glm::vec3 color; //the color of the light
        bool on; //a flag to say if the light is on or off

    public:
        Light();
        Light(glm::vec3 position, glm::vec3 color);
        void turnOn();
        void turnOff();
        glm::vec3 Position;
        glm::vec3 Color;
        bool On;
};