#ifndef SHADER_H
#define SHADER_H

#include <glew.h>
#include "../Loaders/ShaderLoader.h"
#include "Uniform.h"
#include <vector>
#include "glm.hpp"
#include "../GLM/glm/gtc/type_ptr.hpp"
#include "Light.h"

class Shader
{
    private:
        const char* vertex_shader_filepath;
        const char* fragment_shader_filepath;
        GLuint id;
        std::vector<Uniform> uniforms;
        int light_count;
        bool gouraud_lighting; //true for gouraud, false for phong
        bool lights_on;

    public:
        Shader(const char* vertex_filepath, const char* fragment_filepath);
        ~Shader();
        inline GLuint getID(){return id;}
        inline bool isGouraudUsed(){return gouraud_lighting;}
        inline void setGouraudLighting(bool val){gouraud_lighting = val;}
        inline bool lightsOn(){return lights_on;}
        inline void setLightsOn(bool val){lights_on = val;}
        void addUniform(const char* name);
        GLint getUniformID(const char* name);
        float getFloatUniformData(const char* name);
        int getIntegerUniformData(const char* name);
        void setUniformData(const char* name, glm::mat4);
        void setUniformData(const char* name, float);
        void setUniformData(const char* name, int);
        void setUniformData(const char* name, glm::vec3);
};

#endif