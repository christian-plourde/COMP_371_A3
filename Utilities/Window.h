#ifndef COMP_371_A3_WINDOW
#define COMP_371_A3_WINDOW

#include <glew.h>
#include <GLFW/glfw3.h>
#include "glm.hpp"
#include "MVP.h"
#include "Shader.h"
#include "ErrorHandlingFunctions.h"

class Window
{
    private:
        int width;
        int height;
        const char* title;
        glm::vec3 back_color;
        GLFWwindow* window_handle;
        MVP* mvp;
        Shader* shader;
        GLFWwindow* initHandle();

    public:
        Window();
        Window(int width, int height, const char* title);
        ~Window();
        inline const char* getTitle(){return title;}
        inline int getHeight(){return height;}
        inline int getWidth(){return width;}
        inline glm::vec3 getBackColor(){return back_color;}
        inline MVP* getMVP(){return mvp;}
        inline bool isGouraudUsed(){return shader -> isGouraudUsed();}
        void toggleLightModel();
        inline Shader* getShader(){return shader;}
        inline GLuint getShaderID(){return shader -> getID();}
        void setShader(Shader* s);
        inline GLFWwindow* getHandle(){return window_handle;}
        void setBackColor(float red, float green, float blue);
        void set_keyboard_callback(GLFWkeyfun);
        void set_mouse_callback(GLFWmousebuttonfun);
};

#endif