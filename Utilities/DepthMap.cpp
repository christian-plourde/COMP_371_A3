#include "DepthMap.h"

DepthMap::~DepthMap()
{
    delete shader;
}

DepthMap::DepthMap() : SHADOW_WIDTH(1024), SHADOW_HEIGHT(1024){}

DepthMap::DepthMap(GLuint shadow_width, GLuint shadow_height)
{
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
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer));
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_tex, 0));
    GLCall(glDrawBuffer(GL_NONE));
    GLCall(glReadBuffer(GL_NONE));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void DepthMap::setShader(Shader *s)
{
    this -> shader = s;
    GLCall(glUseProgram(shader -> getID()));
}
