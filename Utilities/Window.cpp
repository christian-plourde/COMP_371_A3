#include "Window.h"

Window::Window() : width(800), height(800), title("Window"), back_color(glm::vec3(0,0,0))
{
    window_handle = initHandle();
    glClearColor(back_color.x, back_color.y, back_color.z, 1);
    glfwWindowHint(GLFW_DOUBLEBUFFER, 1);
    glewExperimental = GL_TRUE;
    mvp = new MVP();
    mvp->setProjection(45.0f, width, height, 0.1f, 200.0f);
}

Window::Window(int width, int height, const char* title) : width(800), height(800), back_color(glm::vec3(0,0,0))
{
    window_handle = initHandle();
    glClearColor(back_color.x, back_color.y, back_color.z, 1);
    glfwWindowHint(GLFW_DOUBLEBUFFER, 1);
    glewExperimental = GL_TRUE;
    mvp = new MVP();
    mvp->setProjection(45.0f, width, height, 0.1f, 200.0f);
}

Window::~Window()
{
    delete mvp;
    delete shader;
}

void Window::setBackColor(float red, float green, float blue)
{
    back_color = glm::vec3(red, green, blue);
    glClearColor(back_color.x, back_color.y, back_color.z, 1);
}

GLFWwindow* Window::initHandle()
{
    // Initialize the library
    if (!glfwInit())
        return nullptr;

    window_handle = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window_handle)
    {
        glfwTerminate();
        return nullptr;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window_handle);
    glClearColor(back_color.x, back_color.y, back_color.z, 1); //makes the background color of the window light gray
    //we should also set the keyboard input callback method
    glfwWindowHint(GLFW_DOUBLEBUFFER, 1);

    glewExperimental = GL_TRUE;

    if (GLEW_OK != glewInit())
    {
        return nullptr;
    }

    return window_handle;
}

void Window::set_keyboard_callback(GLFWkeyfun function)
{
    glfwSetKeyCallback(window_handle, function);
}

void Window::set_mouse_callback(GLFWmousebuttonfun function)
{
    glfwSetMouseButtonCallback(window_handle, function);
}

void Window::setShader(Shader* shader)
{
    this -> shader = shader;
}




