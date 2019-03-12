#include <glew.h>
#include <GLFW/glfw3.h>
#include "glm.hpp"
#include "MVP.h"

#ifndef COMP_371_A3_WINDOW
#define COMP_371_A3_WINDOW

class Window
{
    private:
        int width;
        int height;
        const char* title;
        glm::vec3 back_color;
        GLFWwindow* window_handle;
        MVP* mvp;
        GLuint programID; //the id of the currently bound shader

    public:
        Window();
        Window(int width, int height, const char* title);
        ~Window();
        inline const char* getTitle(){return title;}
        inline int getHeight(){return height;}
        inline int getWidth(){return width;}
        inline glm::vec3 getBackColor(){return back_color;}
        inline MVP* getMVP(){return mvp;}
        inline GLuint getShaderID(){return programID;}
        inline void setShaderID(GLuint newID){programID = newID;}
        GLFWwindow* getHandle();
        void setBackColor(float red, float green, float blue);
        void set_keyboard_callback(GLFWkeyfun);
        void set_mouse_callback(GLFWmousebuttonfun);
};

#endif