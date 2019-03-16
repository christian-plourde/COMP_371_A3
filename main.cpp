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
#include "Utilities/Lights/Light.h"
#include "Utilities/Window/Window.h"
#include "Utilities/Objects/Object.h"
#include "Utilities/ErrorHandling/ErrorHandlingFunctions.h"
#include "Utilities/Objects/ObjectContainer.h"
#include "Utilities/ShadowMapping/DepthMap.h"
#include "Utilities/Lights/SpotLight.h"
#include "Utilities/Camera/Camera.h"

Window* myWindow; //the glfw window
ObjectContainer* objects;
Camera* camera;

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
    {
        camera->move_forward();
        //key_press_w(objects);
    }


    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera ->move_backward();
        //key_press_s(objects);
    }


    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera -> move_left();
        //key_press_a(objects);
    }


    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera -> move_right();
        //key_press_d(objects);
    }


    if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        key_press_o(objects);

    if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        key_press_p(objects);

    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        key_press_left_arrow(objects);

    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        key_press_right_arrow(objects);

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        key_press_up_arrow(objects);

    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        key_press_down_arrow(objects);

    if(glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
        key_press_b(objects);

    if(glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        key_press_n(objects);

    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        key_press_e(objects);


    if(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        key_press_j(objects);

    if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        key_press_l(objects);

    if(glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        key_press_i(objects);

    if(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        key_press_k(objects);

    if(glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
        key_press_pg_up(objects);

    if(glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
        key_press_pg_down(objects);

    if(glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
        key_press_F1(objects);

    if(glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
        key_press_F2(objects);
}

int main()
{
    myWindow = new Window();
    myWindow -> set_keyboard_callback(keyboard_callback);
    myWindow -> setBackColor(0.8, 0.8, 0.8);
    objects = new ObjectContainer();

    camera = new Camera("../ObjectFiles/cube.obj");
    camera->load();
    camera->setProjection(60.0f, myWindow->getWidth(), myWindow->getHeight(), 0.1f, 200.0f);
    Shader* camera_shader = new Shader("../Shaders/CameraVertexShader.glsl", "../Shaders/CameraFragmentShader.glsl");
    camera->setShader(camera_shader);
    camera_shader->addUniform("model_matrix");
    camera_shader->addUniform("view_matrix");
    camera_shader->addUniform("projection_matrix");
    camera_shader->setUniformData("model_matrix", camera->getModel());
    camera_shader->setUniformData("view_matrix", camera->getView());
    camera_shader->setUniformData("projection_matrix", camera->getProjection());

    Object heracles("../ObjectFiles/heracles.obj");
    heracles.load();
    MVP heraclesMVP;
    heraclesMVP.setProjection(60.0f, myWindow->getWidth(), myWindow->getHeight(), 0.1f, 200.0f);
    heracles.setMVP(&heraclesMVP);
    heracles.setScreenWidth(myWindow->getWidth());
    heracles.setScreenHeight(myWindow->getHeight());

    Object floor("../ObjectFiles/floor.obj");
    floor.load();
    floor.setMVP(&heraclesMVP);
    MVP floorMVP;
    floorMVP.setProjection(60.0f, myWindow->getWidth(), myWindow->getHeight(), 0.1f, 200.0f);
    floor.setMVP(&floorMVP);
    floor.setAsStatic();
    floor.setScreenWidth(myWindow->getWidth());
    floor.setScreenHeight(myWindow->getHeight());

    //we will also be needing a depth map
    DepthMap depth_map;
    depth_map.load();
    depth_map.setTextureSlot(GL_TEXTURE0);
    //the depth map will have its own shader
    Shader* depth_map_shader = new Shader("../Shaders/DepthMapVertexShader.glsl", "../Shaders/DepthMapFragmentShader.glsl");
    depth_map.setShader(depth_map_shader);
    depth_map_shader->addUniform("light_matrix");
    depth_map_shader->setUniformData("light_matrix", depth_map.getLight()->getLightMatrix());
    depth_map_shader->addUniform("model_matrix");

    Shader* floorShader = new Shader("../Shaders/FloorVertexShader.glsl", "../Shaders/FloorFragmentShader.glsl");
    floor.setShader(floorShader);
    floorShader -> addUniform("view_matrix");
    floorShader -> setUniformData("view_matrix", floor.getMVP() -> getView());
    floorShader -> addUniform("model_matrix");
    floorShader -> setUniformData("model_matrix", floor.getMVP() -> getModel());
    floorShader -> addUniform("projection_matrix");
    floorShader -> setUniformData("projection_matrix", floor.getMVP() -> getProjection());
    floorShader -> addUniform("view_position");
    floorShader -> setUniformData("view_position", glm::vec3(30, 30, 30));
    Light floor_light1(0, 20, 10, 0.2, 0.05, 0.05);
    Light floor_light2(-10, 15, 5, 0.05, 0.2, 0.05);
    Light floor_light3(0, 15, 5, 0.05, 0.05, 0.2);
    Light floor_light4(0, 0, 25, 0.05, 0.05, 0.05);
    floorShader -> addUniform("light_position_1");
    floorShader -> addUniform("light_position_2");
    floorShader -> addUniform("light_position_3");
    floorShader -> addUniform("light_position_4");
    floorShader -> addUniform("light_color_1");
    floorShader -> addUniform("light_color_2");
    floorShader -> addUniform("light_color_3");
    floorShader -> addUniform("light_color_4");
    floorShader -> setUniformData("light_position_1", floor_light1.getPosition());
    floorShader -> setUniformData("light_position_2", floor_light2.getPosition());
    floorShader -> setUniformData("light_position_3", floor_light3.getPosition());
    floorShader -> setUniformData("light_position_4", floor_light4.getPosition());
    floorShader -> setUniformData("light_color_1", floor_light1.getColor());
    floorShader -> setUniformData("light_color_2", floor_light2.getColor());
    floorShader -> setUniformData("light_color_3", floor_light3.getColor());
    floorShader -> setUniformData("light_color_4", floor_light4.getColor());
    SpotLight spot_light_1; //for when we press the F2 key
    spot_light_1.setCutoffAngle(35.0f);
    floorShader -> addUniform("spot_light_1_position");
    floorShader -> setUniformData("spot_light_1_position", spot_light_1.getPosition());
    floorShader -> addUniform("spot_light_1_color");
    floorShader -> setUniformData("spot_light_1_color", spot_light_1.getColor());
    floorShader -> addUniform("spot_light_1_direction");
    floorShader -> setUniformData("spot_light_1_direction", spot_light_1.getDirection());
    floorShader -> addUniform("spot_light_1_cutoff");
    floorShader -> setUniformData("spot_light_1_cutoff", spot_light_1.getCutoffCosine());
    floorShader -> addUniform("depth_tex");
    depth_map.BindForReading();
    floorShader -> setUniformData("depth_tex", depth_map.getTexture());
    floorShader -> addUniform("light_matrix");
    floorShader -> setUniformData("light_matrix", depth_map.getLight()->getLightMatrix());
    floorShader -> addUniform("shadow_map_flag");
    floorShader -> setUniformData("shadow_map_flag", 0);

    Shader* heraclesShader = new Shader("../Shaders/HeraclesVertexShader.glsl", "../Shaders/HeraclesFragmentShader.glsl");
    heracles.setShader(heraclesShader);
    heraclesShader -> addUniform("view_matrix");
    heraclesShader -> setUniformData("view_matrix", heracles.getMVP() -> getView());
    heraclesShader -> addUniform("model_matrix");
    heraclesShader -> setUniformData("model_matrix", heracles.getMVP() -> getModel());
    heraclesShader -> addUniform("projection_matrix");
    heraclesShader -> setUniformData("projection_matrix", heracles.getMVP() -> getProjection());
    heraclesShader -> addUniform("view_position");
    heraclesShader -> setUniformData("view_position", glm::vec3(30, 30, 30));
    Light light1(0, 20, 10, 0.2, 0.05, 0.05);
    Light light2(-10, 15, 5, 0.05, 0.2, 0.05);
    Light light3(0, 15, 5, 0.05, 0.05, 0.2);
    Light light4(0, 0, 25, 0.05, 0.05, 0.05);
    heraclesShader -> addUniform("light_position_1");
    heraclesShader -> addUniform("light_position_2");
    heraclesShader -> addUniform("light_position_3");
    heraclesShader -> addUniform("light_position_4");
    heraclesShader -> addUniform("light_color_1");
    heraclesShader -> addUniform("light_color_2");
    heraclesShader -> addUniform("light_color_3");
    heraclesShader -> addUniform("light_color_4");
    heraclesShader -> setUniformData("light_position_1", light1.getPosition());
    heraclesShader -> setUniformData("light_position_2", light2.getPosition());
    heraclesShader -> setUniformData("light_position_3", light3.getPosition());
    heraclesShader -> setUniformData("light_position_4", light4.getPosition());
    heraclesShader -> setUniformData("light_color_1", light1.getColor());
    heraclesShader -> setUniformData("light_color_2", light2.getColor());
    heraclesShader -> setUniformData("light_color_3", light3.getColor());
    heraclesShader -> setUniformData("light_color_4", light4.getColor());
    heraclesShader -> addUniform("spot_light_1_position");
    heraclesShader -> setUniformData("spot_light_1_position", spot_light_1.getPosition());
    heraclesShader -> addUniform("spot_light_1_color");
    heraclesShader -> setUniformData("spot_light_1_color", spot_light_1.getColor());
    heraclesShader -> addUniform("spot_light_1_direction");
    heraclesShader -> setUniformData("spot_light_1_direction", spot_light_1.getDirection());
    heraclesShader -> addUniform("spot_light_1_cutoff");
    heraclesShader -> setUniformData("spot_light_1_cutoff", spot_light_1.getCutoffCosine());

    objects->addObject(&floor);
    objects->addObject(&heracles);

    while (!glfwWindowShouldClose(myWindow -> getHandle()))
    {
        myWindow->PrepareDraw();

        depth_map.RenderToTexture(objects);
        heracles.setViewPort();
        depth_map.BindForReading();
        camera->Render();
        heracles.Draw();
        floor.Draw();
        myWindow->EndDraw();
    }


    delete objects;
    delete camera;
    delete myWindow;

    glfwTerminate();

    return 0;
}