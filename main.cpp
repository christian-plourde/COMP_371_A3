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
#include "Utilities/Light.h"
#include "Utilities/Window.h"
#include "Utilities/Object.h"
#include "Utilities/ErrorHandlingFunctions.h"
#include "Utilities/ObjectContainer.h"
#include "Utilities/DepthMap.h"

Window* myWindow; //the glfw window

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

    if(glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
        key_press_F1(myWindow);

    if(glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
        key_press_F2(myWindow);
}

int main()
{
    myWindow = new Window();
    myWindow -> set_keyboard_callback(keyboard_callback);
    myWindow -> setBackColor(0.8, 0.8, 0.8);

    Object heracles("../ObjectFiles/heracles.obj");
    heracles.load();
    MVP heraclesMVP;
    heraclesMVP.setProjection(45.0f, myWindow->getWidth(), myWindow->getHeight(), 0.1f, 200.0f);
    heracles.setMVP(&heraclesMVP);

    Shader* basicShader = new Shader("../Shaders/VertexShader.glsl", "../Shaders/FragmentShader.glsl");
    heracles.setShader(basicShader);
    heracles.getShader() -> use();
    basicShader -> addUniform("view_matrix");
    basicShader -> setUniformData("view_matrix", heracles.getMVP() -> getView());
    basicShader -> addUniform("model_matrix");
    basicShader -> setUniformData("model_matrix", heracles.getMVP() -> getModel());
    basicShader -> addUniform("projection_matrix");
    basicShader -> setUniformData("projection_matrix", heracles.getMVP() -> getProjection());
    basicShader -> addUniform("view_position");
    basicShader -> setUniformData("view_position", glm::vec3(20, 20, 20));
    Light light1(0, 20, 10, 0.2, 0.05, 0.05);
    Light light2(-10, 15, 5, 0.05, 0.2, 0.05);
    Light light3(0, 15, 5, 0.05, 0.05, 0.2);
    Light light4(0, 0, 25, 0.05, 0.05, 0.05);
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


    while (!glfwWindowShouldClose(myWindow -> getHandle()))
    {
        myWindow->PrepareDraw();
        heracles.Draw(false);
        myWindow->EndDraw();
    }

    delete myWindow;
    glfwTerminate();

    return 0;
}