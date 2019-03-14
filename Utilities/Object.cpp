#include "Object.h"

Object::Object(const char* filepath) : filepath(filepath)
{
    //when initializing a new object, we will need to generate a new VAO
    GLCall(glGenVertexArrays(1, &VAO));
    GLCall(glBindVertexArray(VAO));
    mesh_type = GL_TRIANGLES;
    static_mode = false;
}

Object::~Object()
{
    delete mvp;
}

bool Object::load()
{
    //function to load an object into the class
    if(!LoadOBJ(filepath, indices, vertices, normals, uvs))
        return false;

    //once we have loaded the data from the file, we should set the data in our buffers

    //next we will need a buffer for the vertices, normals, and uvs
    GLCall(glGenBuffers(1, &vertex_buffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertices.size(), &vertices.front(), GL_STATIC_DRAW));

    GLCall(glGenBuffers(1, &normal_buffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, normal_buffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*normals.size(), &normals.front(), GL_STATIC_DRAW));

    GLCall(glGenBuffers(1, &texture_buffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, texture_buffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*uvs.size(), &uvs.front(), GL_STATIC_DRAW));

    //finally we need an EBO for the indices
    GLCall(glGenBuffers(1, &EBO));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indices.size(), &indices.front(), GL_STATIC_DRAW));
    return true;
}

void Object::Draw(bool use_textures, bool use_shader)
{
    if(use_shader)
        shader -> use();
    //now we can set enable the buffers in our vao
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));

    GLCall(glEnableVertexAttribArray(1));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, normal_buffer));
    GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));

    if(use_textures)
    {
        GLCall(glEnableVertexAttribArray(2));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, texture_buffer));
        GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0));
    }

    //configuring z-buffer
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glDepthFunc(GL_LESS));

    //actual drawing
    GLCall(glDrawArrays(mesh_type, 0, vertices.size()));

    //disable buffers
    GLCall(glDisableVertexAttribArray(0));
    GLCall(glDisableVertexAttribArray(1));

    if(use_textures)
        GLCall(glDisableVertexAttribArray(2));
}

void Object::Draw()
{
    Draw(true, true);
}

void Object::Draw(bool use_textures)
{
    Draw(true, use_textures);
}
