#include "KeyboardControls.h"
#include "../Loaders/ShaderLoader.h"
#include "../GLM/glm/gtc/type_ptr.hpp"
#include <iostream>

void key_press_w(Window* window)
{
    //when the w key is pressed on the keyboard, we should move the camera toward the object
    //this is done by translating the View matrix in the x direction and then resetting the value of the uniform in
    //out shader
    //window -> getMVP() -> setView(glm::translate(window -> getMVP() -> getView(), glm::vec3(0, 0 , -1)));
    //window -> getShader() -> setUniformData("view_matrix", window -> getMVP() -> getView());
}

void key_press_s(Window* window)
{
    //when the s key is pressed on the keyboard, we should move the camera away from the object
    //this is done by translating the View matrix in the x direction and then resetting the value of the uniform in
    //our shader
    //window -> getMVP() -> setView(glm::translate(window -> getMVP() -> getView(), glm::vec3(0, 0 , 1)));
    //window -> getShader() -> setUniformData("view_matrix", window -> getMVP() -> getView());
}

void key_press_a(Window* window)
{
    //when the a key is pressed on the keyboard, we should move the camera to the left the object
    //this is done by translating the View matrix in the x direction and then resetting the value of the uniform in
    //our shader
    //window -> getMVP() -> setView(glm::translate(window -> getMVP() -> getView(), glm::vec3(-1, 0 , 0)));
    //window -> getShader() -> setUniformData("view_matrix", window -> getMVP() -> getView());
}

void key_press_d(Window* window)
{
    //when the d key is pressed on the keyboard, we should move the camera to the right of the object
    //this is done by translating the View matrix in the x direction and then resetting the value of the uniform in
    //our shader
    //window -> getMVP() -> setView(glm::translate(window -> getMVP() -> getView(), glm::vec3(1, 0 , 0)));
    //window -> getShader() -> setUniformData("view_matrix", window -> getMVP() -> getView());
}

void key_press_o(Window* window)
{
    //when the o key is pressed on the keyboard, we should scale the object up by 10%.
    //this is done by scaling the model matrix in all directions and then resetting the value of the uniform in
    //our shader
    //window -> getMVP() -> setModel(glm::scale(window -> getMVP() -> getModel(), glm::vec3(1.01f, 1.01f, 1.01f)));
    //window -> getShader() -> setUniformData("model_matrix", window -> getMVP() -> getModel());
}

void key_press_p(Window* window)
{
    //when the p key is pressed on the keyboard, we should scale the object down by 10%.
    //this is done by scaling the model matrix in all directions and then resetting the value of the uniform in
    //our shader
    //window -> getMVP() -> setModel(glm::scale(window -> getMVP() -> getModel(), glm::vec3(0.99f, 0.99f, 0.99f)));
    //window -> getShader() -> setUniformData("model_matrix", window -> getMVP() -> getModel());
}

void key_press_left_arrow(Window* window)
{
    //when the left arrow is pressed, we need to rotate the camera (i.e the view matrix about the up vector in
    //counterclockwise fashion).
    //window -> getMVP() -> setView(glm::rotate(window -> getMVP() -> getView(), glm::radians(1.5f), glm::vec3(0,1,0)));
    //window -> getShader() -> setUniformData("view_matrix", window -> getMVP() -> getView());
}

void key_press_right_arrow(Window* window)
{
    //when the right arrow is pressed, we need to rotate the camera (i.e the view matrix about the up vector in
    //clockwise fashion).
    //window -> getMVP() -> setView(glm::rotate(window -> getMVP() -> getView(), glm::radians(-1.5f), glm::vec3(0,1,0)));
    //window -> getShader() -> setUniformData("view_matrix", window -> getMVP() -> getView());
}

void key_press_up_arrow(Window* window)
{
    //when the right arrow is pressed, we need to rotate the camera (i.e the view matrix about the up vector in
    //clockwise fashion).
    //window -> getMVP() -> setView(glm::rotate(window -> getMVP() -> getView(), glm::radians(-1.5f), glm::vec3(1,0,0)));
    //window -> getShader() -> setUniformData("view_matrix", window -> getMVP() -> getView());
}

void key_press_down_arrow(Window* window)
{
    //when the right arrow is pressed, we need to rotate the camera (i.e the view matrix about the up vector in
    //clockwise fashion).
    //window -> getMVP() -> setView(glm::rotate(window -> getMVP() -> getView(), glm::radians(1.5f), glm::vec3(1,0,0)));
    //window -> getShader() -> setUniformData("view_matrix", window -> getMVP() -> getView());
}

void key_press_b(Window* window)
{
    //when the b key is pressed, the OBJECT itself (not the camera) should be rotated about the x-axis.
    //in order to do this, we want to modify the Model matrix
    //window -> getMVP() -> setModel(glm::rotate(window -> getMVP() -> getModel(), glm::radians(-0.2f), glm::vec3(1,0,0)));
    //window -> getShader() -> setUniformData("model_matrix", window -> getMVP() -> getModel());
}

void key_press_n(Window* window)
{
    //when the n key is pressed, the OBJECT itself (not the camera) should be rotated about the y-axis.
    //in order to do this, we want to modify the Model matrix
    //window -> getMVP() -> setModel(glm::rotate(window -> getMVP() -> getModel(), glm::radians(0.2f), glm::vec3(0,1,0)));
    //window -> getShader() -> setUniformData("model_matrix", window -> getMVP() -> getModel());
}

void key_press_e(Window* window)
{
    //when the n key is pressed, the OBJECT itself (not the camera) should be rotated about the z-axis.
    //in order to do this, we want to modify the Model matrix
    //window -> getMVP() -> setModel(glm::rotate(window -> getMVP() -> getModel(), glm::radians(1.5f), glm::vec3(0,0,1)));
    //window -> getShader() -> setUniformData("model_matrix", window -> getMVP() -> getModel());
}

void key_press_j(Window* window)
{
    //when the j key is pressed, the OBJECT itself (not the camera) should be translated along the x axis
    //in the positive direction
    //in order to do this, we want to modify the Model matrix
    //window -> getMVP() -> setModel(glm::translate(window -> getMVP() -> getModel(), glm::vec3(0.2f, 0 , 0))) ;
    //window -> getShader() -> setUniformData("model_matrix", window -> getMVP() -> getModel());
}

void key_press_l(Window* window)
{
    //when the l key is pressed, the OBJECT itself (not the camera) should be translated along the x axis
    //in the positive direction
    //in order to do this, we want to modify the Model matrix
    //window -> getMVP() -> setModel(glm::translate(window -> getMVP() -> getModel(), glm::vec3(-0.2f, 0 , 0))) ;
    //window -> getShader() -> setUniformData("model_matrix", window -> getMVP() -> getModel());
}

void key_press_i(Window* window)
{
    //when the i key is pressed, the OBJECT itself (not the camera) should be translated along the y axis
    //in the positive direction
    //in order to do this, we want to modify the Model matrix
    //window -> getMVP() -> setModel(glm::translate(window -> getMVP() -> getModel(), glm::vec3(0, 0.2f , 0))) ;
    //window -> getShader() -> setUniformData("model_matrix", window -> getMVP() -> getModel());
}

void key_press_k(Window* window)
{
    //when the k key is pressed, the OBJECT itself (not the camera) should be translated along the y axis
    //in the negative direction
    //in order to do this, we want to modify the Model matrix
    //window -> getMVP() -> setModel(glm::translate(window -> getMVP() -> getModel(), glm::vec3(0, -0.2f , 0))) ;
    //window -> getShader() -> setUniformData("model_matrix", window -> getMVP() -> getModel());
}

void key_press_pg_up(Window* window)
{
    //when the page up key is pressed, the OBJECT itself (not the camera) should be translated along the z axis
    //in the positive direction
    //in order to do this, we want to modify the Model matrix
    //window -> getMVP() -> setModel(glm::translate(window -> getMVP() -> getModel(), glm::vec3(0, 0 , 0.2f))) ;
    //window -> getShader() -> setUniformData("model_matrix", window -> getMVP() -> getModel());
}

void key_press_pg_down(Window* window)
{
    //when the page down key is pressed, the OBJECT itself (not the camera) should be translated along the z axis
    //in the negative direction
    //in order to do this, we want to modify the Model matrix
    //window -> getMVP() -> setModel(glm::translate(window -> getMVP() -> getModel(), glm::vec3(0, 0 , -0.2f))) ;
    //window -> getShader() -> setUniformData("model_matrix", window -> getMVP() -> getModel());
}

void key_press_F1(Window* window)
{
    //when the F1 key is pressed, it should toggle between the scene having the 4 lights or only one
    //in order to do this, we can
    //if(window -> getShader() -> lightsOn())
    //{
        //if the lights are on, we should make all of them dark except the first light and change its color
        //and position to match the definition in part B
    //    window -> getShader() -> setUniformData("light_position_1", glm::vec3(0,20,10));
    //    window -> getShader() -> setUniformData("light_color_1", glm::vec3(0,0,0));
    //    window -> getShader() -> setUniformData("light_color_2", glm::vec3(0,0,0));
    //    window -> getShader() -> setUniformData("light_color_3", glm::vec3(0,0,0));
     //   window -> getShader() -> setUniformData("light_color_4", glm::vec3(0,0,0));
     //   window -> getShader() -> setLightsOn(false);
    //}

    //else
    //{
      //  window -> getShader() -> setUniformData("light_position_1", glm::vec3(0,20,10));
       // window -> getShader() -> setUniformData("light_color_1", glm::vec3(0.2,0.05,0.05));
       // window -> getShader() -> setUniformData("light_color_2", glm::vec3(0.05,0.2,0.05));
        //window -> getShader() -> setUniformData("light_color_3", glm::vec3(0.05,0.05,0.2));
        //window -> getShader() -> setUniformData("light_color_4", glm::vec3(0.05,0.05,0.05));
        //window -> getShader() -> setLightsOn(true);
    //}
}

void key_press_F2(Window* window)
{
    //first make sure only one light is being used (the one in the assignment description)
    //window -> getShader() -> setUniformData("light_position_1", glm::vec3(0,20,10));
    //window -> getShader() -> setUniformData("light_color_1", glm::vec3(0.8,0.2,0.2));
    //window -> getShader() -> setUniformData("light_color_2", glm::vec3(0,0,0));
    //window -> getShader() -> setUniformData("light_color_3", glm::vec3(0,0,0));
    //window -> getShader() -> setUniformData("light_color_4", glm::vec3(0,0,0));
}