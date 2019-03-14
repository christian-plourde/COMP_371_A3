#ifndef DEPTH_MAP_H
#define DEPTH_MAP_H

#include <glew.h>
#include "Shader.h"
#include "ErrorHandlingFunctions.h"
#include "Window.h"
#include "ObjectContainer.h"
#include "DepthMapLight.h"

class DepthMap
{
    private:
        GLuint frame_buffer;
        GLuint depth_tex;
        GLuint SHADOW_HEIGHT;
        GLuint SHADOW_WIDTH;
        Shader* shader;
        DepthMapLight* depth_light;

    public:
        DepthMap();
        DepthMap(GLuint shadow_width, GLuint shadow_height);
        ~DepthMap();
        inline DepthMapLight* getLight(){return depth_light;}
        void setShader(Shader* s);
        void load();
        void RenderToTexture(Window* window, ObjectContainer* o);
};

#endif