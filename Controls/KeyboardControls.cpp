#include "KeyboardControls.h"
#include "../Loaders/ShaderLoader.h"
#include "../GLM/glm/gtc/type_ptr.hpp"
#include <iostream>

void key_press_w(Window* window)
{
    //when the w key is pressed on the keyboard, we should move the camera toward the object
    //this is done by translating the View matrix in the x direction and then resetting the value of the uniform in
    //out shader
    window -> getMVP() -> setView(glm::translate(window -> getMVP() -> getView(), glm::vec3(0, 0 , -1)));
    window -> getShader() -> setUniformData("view_matrix", window -> getMVP() -> getView());
}

void key_press_s(Window* window)
{
    //when the s key is pressed on the keyboard, we should move the camera away from the object
    //this is done by translating the View matrix in the x direction and then resetting the value of the uniform in
    //our shader
    window -> getMVP() -> setView(glm::translate(window -> getMVP() -> getView(), glm::vec3(0, 0 , 1)));
    window -> getShader() -> setUniformData("view_matrix", window -> getMVP() -> getView());
}

void key_press_a(Window* window)
{
    //when the a key is pressed on the keyboard, we should move the camera to the left the object
    //this is done by translating the View matrix in the x direction and then resetting the value of the uniform in
    //our shader
    window -> getMVP() -> setView(glm::translate(window -> getMVP() -> getView(), glm::vec3(-1, 0 , 0)));
    window -> getShader() -> setUniformData("view_matrix", window -> getMVP() -> getView());
}

void key_press_d(Window* window)
{
    //when the d key is pressed on the keyboard, we should move the camera to the right of the object
    //this is done by translating the View matrix in the x direction and then resetting the value of the uniform in
    //our shader
    window -> getMVP() -> setView(glm::translate(window -> getMVP() -> getView(), glm::vec3(1, 0 , 0)));
    window -> getShader() -> setUniformData("view_matrix", window -> getMVP() -> getView());
}

void key_press_o(Window* window)
{
    //when the o key is pressed on the keyboard, we should scale the object up by 10%.
    //this is done by scaling the model matrix in all directions and then resetting the value of the uniform in
    //our shader
    window -> getMVP() -> setModel(glm::scale(window -> getMVP() -> getModel(), glm::vec3(1.01f, 1.01f, 1.01f)));
    window -> getShader() -> setUniformData("model_matrix", window -> getMVP() -> getModel());
}

void key_press_p(Window* window)
{
    //when the p key is pressed on the keyboard, we should scale the object down by 10%.
    //this is done by scaling the model matrix in all directions and then resetting the value of the uniform in
    //our shader
    window -> getMVP() -> setModel(glm::scale(window -> getMVP() -> getModel(), glm::vec3(0.99f, 0.99f, 0.99f)));
    window -> getShader() -> setUniformData("model_matrix", window -> getMVP() -> getModel());
}

void key_press_left_arrow(Window* window)
{
    //when the left arrow is pressed, we need to rotate the camera (i.e the view matrix about the up vector in
    //counterclockwise fashion).
    window -> getMVP() -> setView(glm::rotate(window -> getMVP() -> getView(), glm::radians(1.5f), glm::vec3(0,1,0)));
    window -> getShader() -> setUniformData("view_matrix", window -> getMVP() -> getView());
}

void key_press_right_arrow(Window* window)
{
    //when the right arrow is pressed, we need to rotate the camera (i.e the view matrix about the up vector in
    //clockwise fashion).
    window -> getMVP() -> setView(glm::rotate(window -> getMVP() -> getView(), glm::radians(-1.5f), glm::vec3(0,1,0)));
    window -> getShader() -> setUniformData("view_matrix", window -> getMVP() -> getView());
}

void key_press_up_arrow(Window* window)
{
    //when the right arrow is pressed, we need to rotate the camera (i.e the view matrix about the up vector in
    //clockwise fashion).
    window -> getMVP() -> setView(glm::rotate(window -> getMVP() -> getView(), glm::radians(-1.5f), glm::vec3(1,0,0)));
    window -> getShader() -> setUniformData("view_matrix", window -> getMVP() -> getView());
}

void key_press_down_arrow(Window* window)
{
    //when the right arrow is pressed, we need to rotate the camera (i.e the view matrix about the up vector in
    //clockwise fashion).
    window -> getMVP() -> setView(glm::rotate(window -> getMVP() -> getView(), glm::radians(1.5f), glm::vec3(1,0,0)));
    window -> getShader() -> setUniformData("view_matrix", window -> getMVP() -> getView());
}

void key_press_b(Window* window)
{
    //when the b key is pressed, the OBJECT itself (not the camera) should be rotated about the x-axis.
    //in order to do this, we want to modify the Model matrix
    window -> getMVP() -> setModel(glm::rotate(window -> getMVP() -> getModel(), glm::radians(-0.2f), glm::vec3(1,0,0)));
    window -> getShader() -> setUniformData("model_matrix", window -> getMVP() -> getModel());
}

void key_press_n(Window* window)
{
    //when the n key is pressed, the OBJECT itself (not the camera) should be rotated about the y-axis.
    //in order to do this, we want to modify the Model matrix
    window -> getMVP() -> setModel(glm::rotate(window -> getMVP() -> getModel(), glm::radians(0.2f), glm::vec3(0,1,0)));
    window -> getShader() -> setUniformData("model_matrix", window -> getMVP() -> getModel());
}

void key_press_e(Window* window)
{
    //when the n key is pressed, the OBJECT itself (not the camera) should be rotated about the z-axis.
    //in order to do this, we want to modify the Model matrix
    window -> getMVP() -> setModel(glm::rotate(window -> getMVP() -> getModel(), glm::radians(1.5f), glm::vec3(0,0,1)));
    window -> getShader() -> setUniformData("model_matrix", window -> getMVP() -> getModel());
}

void key_press_j(Window* window)
{
    //when the j key is pressed, the OBJECT itself (not the camera) should be translated along the x axis
    //in the positive direction
    //in order to do this, we want to modify the Model matrix
    window -> getMVP() -> setModel(glm::translate(window -> getMVP() -> getModel(), glm::vec3(0.2f, 0 , 0))) ;
    window -> getShader() -> setUniformData("model_matrix", window -> getMVP() -> getModel());
}

void key_press_l(Window* window)
{
    //when the l key is pressed, the OBJECT itself (not the camera) should be translated along the x axis
    //in the positive direction
    //in order to do this, we want to modify the Model matrix
    window -> getMVP() -> setModel(glm::translate(window -> getMVP() -> getModel(), glm::vec3(-0.2f, 0 , 0))) ;
    window -> getShader() -> setUniformData("model_matrix", window -> getMVP() -> getModel());
}

void key_press_i(Window* window)
{
    //when the i key is pressed, the OBJECT itself (not the camera) should be translated along the y axis
    //in the positive direction
    //in order to do this, we want to modify the Model matrix
    window -> getMVP() -> setModel(glm::translate(window -> getMVP() -> getModel(), glm::vec3(0, 0.2f , 0))) ;
    window -> getShader() -> setUniformData("model_matrix", window -> getMVP() -> getModel());
}

void key_press_k(Window* window)
{
    //when the k key is pressed, the OBJECT itself (not the camera) should be translated along the y axis
    //in the negative direction
    //in order to do this, we want to modify the Model matrix
    window -> getMVP() -> setModel(glm::translate(window -> getMVP() -> getModel(), glm::vec3(0, -0.2f , 0))) ;
    window -> getShader() -> setUniformData("model_matrix", window -> getMVP() -> getModel());
}

void key_press_pg_up(Window* window)
{
    //when the page up key is pressed, the OBJECT itself (not the camera) should be translated along the z axis
    //in the positive direction
    //in order to do this, we want to modify the Model matrix
    window -> getMVP() -> setModel(glm::translate(window -> getMVP() -> getModel(), glm::vec3(0, 0 , 0.2f))) ;
    window -> getShader() -> setUniformData("model_matrix", window -> getMVP() -> getModel());
}

void key_press_pg_down(Window* window)
{
    //when the page down key is pressed, the OBJECT itself (not the camera) should be translated along the z axis
    //in the negative direction
    //in order to do this, we want to modify the Model matrix
    window -> getMVP() -> setModel(glm::translate(window -> getMVP() -> getModel(), glm::vec3(0, 0 , -0.2f))) ;
    window -> getShader() -> setUniformData("model_matrix", window -> getMVP() -> getModel());
}

void key_press_1(Window* window)
{
    //when this key is pressed, we first need to find the id of the red channel uniform in the shader program
    float curr_val = window -> getShader() -> getFloatUniformData("red_channel");

    if(curr_val == 1.0f)
        window -> getShader() -> setUniformData("red_channel", 0.0f);
    else
        window -> getShader() -> setUniformData("red_channel", 1.0f);

    //this changes the value of the red_channel from 1 to 0 or zero to 1 depending on what the current value is
}

void key_press_2(Window* window)
{
    //this method works exactly in the same way as the one for the red channel, the only difference is that here
    //we are modifying the green channel's value

    float curr_val = window -> getShader() -> getFloatUniformData("green_channel");

    if(curr_val == 1.0f)
        window -> getShader() -> setUniformData("green_channel", 0.0f);
    else
        window -> getShader() -> setUniformData("green_channel", 1.0f);
}

void key_press_3(Window* window)
{
    //this method works exactly in the same way as the one for the red channel, the only difference is that here
    //we are modifying the blue channel's value

    float curr_val = window -> getShader() -> getFloatUniformData("blue_channel");

    if(curr_val == 1.0f)
        window -> getShader() -> setUniformData("blue_channel", 0.0f);
    else
        window -> getShader() -> setUniformData("blue_channel", 1.0f);
}

void key_press_4(Window* window)
{
    //when the '4' key is pressed on the keyboard, all of the channels should be toggled on.
    window -> getShader() -> setUniformData("red_channel", 1.0f);
    window -> getShader() -> setUniformData("green_channel", 1.0f);
    window -> getShader() -> setUniformData("blue_channel", 1.0f);
}

void key_press_6(Window* window)
{
    //if the light is on, then we should turn it off and vice versa
    int curr_val = window -> getShader() -> getIntegerUniformData("light_on");

    if(curr_val == 1)
        window -> getShader() -> setUniformData("light_on", 0);
    else
        window -> getShader() -> setUniformData("light_on", 1);
}

void key_press_5(Window* window)
{
    //there are two cases, either gouraud is true, in which case, we should switch the value of the uniform for gouraud
    //it is false, and we should load the gouraud shaders and flip it.
    if(window -> isGouraudUsed())
    {
        std::cout << "Switching to Phong Illumination Model..." << std::endl;
        window -> getShader() -> setUniformData("gouraudUsed", 0);
        window -> toggleLightModel();
    }

    else
    {
        std::cout << "Switching to Gouraud Illumination Model..." << std::endl;
        window -> getShader() -> setUniformData("gouraudUsed", 1);
        window -> toggleLightModel();
    }
}

void key_press_m(Window* window)
{
    //first we must check the value of the uniform
    int flag_value = window -> getShader() -> getIntegerUniformData("normal_as_color");

    //now that we have the current value, we should flip it
    if(flag_value == 1)
        window -> getShader() -> setUniformData("normal_as_color", 0);

    else
        window -> getShader() -> setUniformData("normal_as_color", 1);
}

void key_press_g(Window* window)
{
    //first we must check the value of the uniform
    int flag_value = window -> getShader() -> getIntegerUniformData("gray_scale");

    //now that we have the current value, we should flip it
    if(flag_value == 1)
        window -> getShader() -> setUniformData("gray_scale", 0);

    else
        window -> getShader() -> setUniformData("gray_scale", 1);
}

void key_press_F1(Window* window)
{
    //when the F1 key is pressed, it should toggle between the scene having the 4 lights or only one
    //in order to do this, we can
    if(window -> getShader() -> lightsOn())
    {
        //if the lights are on, we should make all of them dark except the first light and change its color
        //and position to match the definition in part B
        window -> getShader() -> setUniformData("light_position_1", glm::vec3(0,20,10));
        window -> getShader() -> setUniformData("light_color_1", glm::vec3(0.8,0.2,0.2));
        window -> getShader() -> setUniformData("light_color_2", glm::vec3(0,0,0));
        window -> getShader() -> setUniformData("light_color_3", glm::vec3(0,0,0));
        window -> getShader() -> setUniformData("light_color_4", glm::vec3(0,0,0));
        window -> getShader() -> setLightsOn(false);
    }

    else
    {
        window -> getShader() -> setUniformData("light_position_1", glm::vec3(0,20,10));
        window -> getShader() -> setUniformData("light_color_1", glm::vec3(0.8,0.2,0.2));
        window -> getShader() -> setUniformData("light_color_2", glm::vec3(0.05,0.2,0.05));
        window -> getShader() -> setUniformData("light_color_3", glm::vec3(0.05,0.05,0.2));
        window -> getShader() -> setUniformData("light_color_4", glm::vec3(0.05,0.05,0.05));
        window -> getShader() -> setLightsOn(true);
    }
}

void key_press_F2(Window* window)
{
    //first make sure only one light is being used (the one in the assignment description)
    window -> getShader() -> setUniformData("light_position_1", glm::vec3(0,20,10));
    window -> getShader() -> setUniformData("light_color_1", glm::vec3(0.8,0.2,0.2));
    window -> getShader() -> setUniformData("light_color_2", glm::vec3(0,0,0));
    window -> getShader() -> setUniformData("light_color_3", glm::vec3(0,0,0));
    window -> getShader() -> setUniformData("light_color_4", glm::vec3(0,0,0));
}