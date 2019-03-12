#ifndef OBJECT_H
#define OBJECT_H

#include <glew.h>
#include "../Loaders/ObjectLoader.h"
#include <vector>
#include "glm.hpp"
#include "ErrorHandlingFunctions.h"
#include "Window.h"

class Object
{
    private:
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
        const char* filepath;
        Window* window;

    public:
        Object(const char* filepath);
        ~Object();
        bool load();
        void Draw(bool use_textures);
        void DrawAsSingle(bool use_textures);
        inline std::vector<glm::vec3> getVertices(){return vertices;}
        inline std::vector<glm::vec3> getNormals(){return normals;}
        inline std::vector<glm::vec2> getUVS(){return uvs;}
        inline std::vector<int> getIndices(){return indices;}
        inline void setFilePath(const char* path){filepath = path;}
        inline void setWindow(Window* w){window = w;}
        inline Window* getWindow(){return window;}
        inline const char* getFilePath(){return filepath;}
        inline void setMeshType(GLuint mesh){mesh_type = mesh;}
};

#endif