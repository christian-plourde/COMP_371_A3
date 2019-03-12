#include <iostream>
#include <string>
#include <sstream>
#include <glew.h>
#include <GLFW/glfw3.h>
#include "GLM/glm/matrix.hpp"
#include "GLM/glm/gtc/matrix_transform.hpp"
#include "GLM/glm/gtc/type_ptr.hpp"
#include "Loaders/ShaderLoader.h"
#include "Loaders/ObjectLoader.h"
#include "Controls/KeyboardControls.h"
#include "Controls/MouseControls.h"
#include "Utilities/Light.h"
#include "Utilities/Window.h"
#include "Utilities/Object.h"
#include "Utilities/ErrorHandlingFunctions.h"
#include "Utilities/ObjectContainer.h"
#include "Utilities/DepthMap.h"

Window* myWindow; //the glfw window

GLuint depthMapProgramID; //the id for the shader program used to render the depth map

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    /*
     * This defines what happens when the escape key is pressed. In our case, we would like the escape key to close
     * the currently used window
     */
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    //here we define what occurs if specific keys are pressed
    //the functions are defined in the keyboard controls file, we are simply calling them based on
    //which key is pressed

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        key_press_w(myWindow);

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        key_press_s(myWindow);

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        key_press_a(myWindow);

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        key_press_d(myWindow);

    if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        key_press_o(myWindow);

    if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        key_press_p(myWindow);

    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        key_press_left_arrow(myWindow);

    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        key_press_right_arrow(myWindow);

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        key_press_up_arrow(myWindow);

    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        key_press_down_arrow(myWindow);

    if(glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
        key_press_b(myWindow);

    if(glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        key_press_n(myWindow);

    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        key_press_e(myWindow);


    if(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        key_press_j(myWindow);

    if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        key_press_l(myWindow);

    if(glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        key_press_i(myWindow);

    if(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        key_press_k(myWindow);

    if(glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
        key_press_pg_up(myWindow);

    if(glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
        key_press_pg_down(myWindow);

    //controls what occurs when the '1' key is pressed
    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        key_press_1(myWindow);

    //controls what happens when the '2' key is pressed
    if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        key_press_2(myWindow);

    //controls what happens when the '3' key is pressed
    if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        key_press_3(myWindow);

    if(glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        key_press_4(myWindow);

    if(glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
        key_press_6(myWindow);

    if(glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        key_press_5(myWindow);
    }

    if(glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        key_press_m(myWindow);

    if(glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        key_press_g(myWindow);


    if(glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
        key_press_F1(myWindow);


    if(glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
        key_press_F2(myWindow);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        key_press_lm_button_down(myWindow);

    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        key_press_rm_button_down(myWindow);
}

/*
 * This method takes care of arranging the proper shader program for the first pass render in the depth map so that
 * we render to the depth map and not the actual scene.
 */
void DepthMapPass()
{
    //first set the program id to use our depth map shaders
    glUseProgram(depthMapProgramID);

    //next we establish the light_matrix that will be used.
    float near_plane = 1.0f, far_plane = 7.5f;
    glm::mat4 lightProjection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, near_plane, far_plane);

    glm::mat4 lightView = glm::lookAt(glm::vec3(0,20,10), glm::vec3(0,0,0), glm::vec3(0,0,0));

    glm::mat4 lightSpaceMatrix = lightProjection * lightView;
    glUniform4fv(glGetUniformLocation(myWindow->getShaderID(), "light_matrix"), 1, glm::value_ptr(lightSpaceMatrix));
}

int main()
{
    myWindow = new Window();
    myWindow -> set_keyboard_callback(keyboard_callback);
    myWindow -> set_mouse_callback(mouse_button_callback);
    myWindow -> setBackColor(0.8, 0.8, 0.8);
    Shader* depthMapShader = new Shader("../Shaders/DepthMapVertexShader.glsl", "../Shaders/DepthMapFragmentShader.glsl");
    DepthMap depthMap;
    depthMap.load();
    depthMap.setShader(depthMapShader);

    Shader* basicShader = new Shader("../Shaders/VertexShader.glsl", "../Shaders/FragmentShader.glsl");
    myWindow -> setShader(basicShader);
    basicShader -> addUniform("view_matrix");
    basicShader -> setUniformData("view_matrix", myWindow -> getMVP() -> getView());
    basicShader -> addUniform("model_matrix");
    basicShader -> setUniformData("model_matrix", myWindow -> getMVP() -> getModel());
    basicShader -> addUniform("projection_matrix");
    basicShader -> setUniformData("projection_matrix", myWindow -> getMVP() -> getProjection());
    basicShader -> addUniform("red_channel");
    basicShader -> setUniformData("red_channel", 1.0f);
    basicShader -> addUniform("blue_channel");
    basicShader -> setUniformData("blue_channel", 1.0f);
    basicShader -> addUniform("green_channel");
    basicShader -> setUniformData("green_channel", 1.0f);
    basicShader -> addUniform("light_on");
    basicShader -> setUniformData("light_on", 1);
    basicShader -> addUniform("normal_as_color");
    basicShader -> setUniformData("normal_as_color", 0);
    basicShader -> addUniform("gray_scale");
    basicShader -> setUniformData("gray_scale", 0);
    basicShader -> addUniform("view_position");
    basicShader -> setUniformData("view_position", glm::vec3(100, 100, 100));
    basicShader -> addUniform("gouraudUsed");
    basicShader -> setUniformData("gouraudUsed", 0);
    Light light1(0, 20, 10, 0.8, 0.2, 0.2);
    Light light2(-10, 15, 5, 0, 0, 0);
    Light light3(0, 15, 5, 0, 0, 0);
    Light light4(0, 0, 25, 0, 0, 0);
    basicShader -> addUniform("light_position_1");
    basicShader -> addUniform("light_position_2");
    basicShader -> addUniform("light_position_3");
    basicShader -> addUniform("light_position_4");
    basicShader -> addUniform("light_color_1");
    basicShader -> addUniform("light_color_2");
    basicShader -> addUniform("light_color_3");
    basicShader -> addUniform("light_color_4");
    basicShader -> setUniformData("light_position_1", light1.getPosition());
    basicShader -> setUniformData("light_position_2", light2.getPosition());
    basicShader -> setUniformData("light_position_3", light3.getPosition());
    basicShader -> setUniformData("light_position_4", light4.getPosition());
    basicShader -> setUniformData("light_color_1", light1.getColor());
    basicShader -> setUniformData("light_color_2", light2.getColor());
    basicShader -> setUniformData("light_color_3", light3.getColor());
    basicShader -> setUniformData("light_color_4", light4.getColor());

    Object heracles("../ObjectFiles/heracles.obj");
    heracles.setWindow(myWindow);
    heracles.load();

    Object floor("../ObjectFiles/floor.obj");
    floor.setWindow(myWindow);
    floor.load();

    ObjectContainer objects;
    objects.addObject(heracles);
    objects.addObject(floor);

    /******************************************* DEPTH MAP DEFINITION ****************************************/


    /****************************************** END DEPTH MAP DEFINITION *************************************/

    /************************************* SHADER LOADING ***************************************************/
    //now we load the shader program and assign it to our program id
    //initially, we use the Phong illumination model

    //we should also load the depth map shader set
    depthMapProgramID = LoadShaders("../Shaders/DepthMapVertexShader.glsl", "../Shaders/DepthMapFragmentShader.glsl");

    /************************************* DONE SHADER LOADING ***************************************************/

    /************************************* MODEL VIEW PROJECTION INSTANTIATION **************************************/
    //in order for this object to be viewed from a perspective view, we need a Model View Projection matrix
    //we wish to draw the triangle from a perspective view
    //this is the projection matrix for a perspective view


    /************************************* DONE MODEL VIEW PROJECTION INSTANTIATION ******************************/

    //we need to define two doubles to hold the old and new positions of the mouse cursor so we can check
    //which direction the user is moving the mouse in.

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(myWindow -> getHandle()))
    {
        //first pass, in which we render to the depth map
        /*
        GLCall(glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT));
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, depthBuffer));
        GLCall(glClear(GL_DEPTH_BUFFER_BIT));
        DepthMapPass();
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
         */

        objects.DrawAll(false);
    }

    delete myWindow;
    glfwTerminate();

    return 0;
}