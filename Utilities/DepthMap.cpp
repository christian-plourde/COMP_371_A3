#include "DepthMap.h"

DepthMap::~DepthMap()
{
    delete shader;
    delete depth_light;
}

DepthMap::DepthMap() : SHADOW_WIDTH(1024), SHADOW_HEIGHT(1024)
{
    depth_light = new DepthMapLight();
}

DepthMap::DepthMap(GLuint shadow_width, GLuint shadow_height)
{
    depth_light = new DepthMapLight();
    SHADOW_HEIGHT = shadow_height;
    SHADOW_WIDTH = shadow_width;
}

void DepthMap::load()
{
    //when we load a depth map, the first thing we need to do is initialize our framebuffer as well as our
    //depth texture
    GLCall(glGenFramebuffers(1, &frame_buffer));
    GLCall(glGenTextures(1, &depth_tex));
    GLCall(glBindTexture(GL_TEXTURE_2D, depth_tex));
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0,GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
    GLCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer));
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_tex, 0));
    GLCall(glDrawBuffer(GL_NONE));
    GLCall(glReadBuffer(GL_NONE));

}

void DepthMap::setShader(Shader *s)
{
    this -> shader = s;
}

void DepthMap::RenderToTexture(ObjectContainer *o)
{
    //in this method we want to render the scene from the perspective of the depth map
    shader -> use();
    GLCall(glViewport(0,0, SHADOW_WIDTH, SHADOW_HEIGHT));
    BindForWriting();
    GLCall(glClear(GL_DEPTH_BUFFER_BIT));
    for(int i = 0; i < o->size; i++)
    {
        //draw each object using the shader bound to the depth map
        o->getObject(i)->Draw(false, false);
    }
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void DepthMap::BindForWriting()
{
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer));
}

void DepthMap::BindForReading(GLenum tex_unit)
{
    GLCall(glActiveTexture(tex_unit));
    GLCall(glBindTexture(GL_TEXTURE_2D, depth_tex));
}

