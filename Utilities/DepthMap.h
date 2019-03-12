#ifndef DEPTH_MAP_H
#define DEPTH_MAP_H

#include <glew.h>
#include "Shader.h"
#include "ErrorHandlingFunctions.h"

class DepthMap
{
    private:
        GLuint frame_buffer;
        GLuint depth_tex;
        GLuint SHADOW_HEIGHT;
        GLuint SHADOW_WIDTH;
        Shader* shader;

    public:
        DepthMap();
        DepthMap(GLuint shadow_width, GLuint shadow_height);
        ~DepthMap();
        void setShader(Shader* s);
        void load();
};

#endif