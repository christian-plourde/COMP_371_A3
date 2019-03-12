#include "ObjectContainer.h"

ObjectContainer::ObjectContainer() {}

ObjectContainer::~ObjectContainer() {}

void ObjectContainer::addObject(Object obj)
{
    objects.push_back(obj);
}

void ObjectContainer::DrawAll(bool use_textures)
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    for(int i = 0; i < objects.size(); i++)
    {
        //for each object in the container call draw.
        objects[i].Draw(use_textures);
    }

    //once we have drawn everything, we swap the buffers and poll
    if(!objects.empty())
        GLCall(glfwSwapBuffers(objects[0].getWindow() -> getHandle()));

    GLCall(glfwPollEvents());
}

