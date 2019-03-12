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
    GLuint MatrixID = glGetUniformLocation(window -> getShaderID(), "view_matrix");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(window -> getMVP() -> getView()[0][0]));
}

void key_press_s(Window* window)
{
    //when the s key is pressed on the keyboard, we should move the camera away from the object
    //this is done by translating the View matrix in the x direction and then resetting the value of the uniform in
    //our shader
    window -> getMVP() -> setView(glm::translate(window -> getMVP() -> getView(), glm::vec3(0, 0 , 1)));
    GLuint MatrixID = glGetUniformLocation(window -> getShaderID(), "view_matrix");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(window -> getMVP() -> getView()[0][0]));
}

void key_press_a(Window* window)
{
    //when the a key is pressed on the keyboard, we should move the camera to the left the object
    //this is done by translating the View matrix in the x direction and then resetting the value of the uniform in
    //our shader
    window -> getMVP() -> setView(glm::translate(window -> getMVP() -> getView(), glm::vec3(-1, 0 , 0)));
    GLuint MatrixID = glGetUniformLocation(window -> getShaderID(), "view_matrix");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(window -> getMVP() -> getView()[0][0]));
}

void key_press_d(Window* window)
{
    //when the d key is pressed on the keyboard, we should move the camera to the right of the object
    //this is done by translating the View matrix in the x direction and then resetting the value of the uniform in
    //our shader
    window -> getMVP() -> setView(glm::translate(window -> getMVP() -> getView(), glm::vec3(1, 0 , 0)));
    GLuint MatrixID = glGetUniformLocation(window -> getShaderID(), "view_matrix");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(window -> getMVP() -> getView()[0][0]));
}

void key_press_o(Window* window)
{
    //when the o key is pressed on the keyboard, we should scale the object up by 10%.
    //this is done by scaling the model matrix in all directions and then resetting the value of the uniform in
    //our shader
    window -> getMVP() -> setModel(glm::scale(window -> getMVP() -> getModel(), glm::vec3(1.01f, 1.01f, 1.01f)));
    GLuint MatrixID = glGetUniformLocation(window -> getShaderID(), "model_matrix");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(window -> getMVP() -> getModel()[0][0]));
}

void key_press_p(Window* window)
{
    //when the p key is pressed on the keyboard, we should scale the object down by 10%.
    //this is done by scaling the model matrix in all directions and then resetting the value of the uniform in
    //our shader
    window -> getMVP() -> setModel(glm::scale(window -> getMVP() -> getModel(), glm::vec3(0.99f, 0.99f, 0.99f)));
    GLuint MatrixID = glGetUniformLocation(window -> getShaderID(), "model_matrix");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(window -> getMVP() -> getModel()[0][0]));
}

void key_press_left_arrow(Window* window)
{
    //when the left arrow is pressed, we need to rotate the camera (i.e the view matrix about the up vector in
    //counterclockwise fashion).
    window -> getMVP() -> setView(glm::rotate(window -> getMVP() -> getView(), glm::radians(1.5f), glm::vec3(0,1,0)));
    GLuint MatrixID = glGetUniformLocation(window -> getShaderID(), "view_matrix");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(window -> getMVP() -> getView()[0][0]));
}

void key_press_right_arrow(Window* window)
{
    //when the right arrow is pressed, we need to rotate the camera (i.e the view matrix about the up vector in
    //clockwise fashion).
    window -> getMVP() -> setView(glm::rotate(window -> getMVP() -> getView(), glm::radians(-1.5f), glm::vec3(0,1,0)));
    GLuint MatrixID = glGetUniformLocation(window -> getShaderID(), "view_matrix");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(window -> getMVP() -> getView()[0][0]));
}

void key_press_up_arrow(Window* window)
{
    //when the right arrow is pressed, we need to rotate the camera (i.e the view matrix about the up vector in
    //clockwise fashion).
    window -> getMVP() -> setView(glm::rotate(window -> getMVP() -> getView(), glm::radians(-1.5f), glm::vec3(1,0,0)));
    GLuint MatrixID = glGetUniformLocation(window -> getShaderID(), "view_matrix");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(window -> getMVP() -> getView()[0][0]));
}

void key_press_down_arrow(Window* window)
{
    //when the right arrow is pressed, we need to rotate the camera (i.e the view matrix about the up vector in
    //clockwise fashion).
    window -> getMVP() -> setView(glm::rotate(window -> getMVP() -> getView(), glm::radians(1.5f), glm::vec3(1,0,0)));
    GLuint MatrixID = glGetUniformLocation(window -> getShaderID(), "view_matrix");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(window -> getMVP() -> getView()[0][0]));
}

void key_press_b(Window* window)
{
    //when the b key is pressed, the OBJECT itself (not the camera) should be rotated about the x-axis.
    //in order to do this, we want to modify the Model matrix
    window -> getMVP() -> setModel(glm::rotate(window -> getMVP() -> getModel(), glm::radians(-0.2f), glm::vec3(1,0,0)));
    GLuint MatrixID = glGetUniformLocation(window -> getShaderID(), "model_matrix");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(window -> getMVP() -> getModel()[0][0]));
}

void key_press_n(Window* window)
{
    //when the n key is pressed, the OBJECT itself (not the camera) should be rotated about the y-axis.
    //in order to do this, we want to modify the Model matrix
    window -> getMVP() -> setModel(glm::rotate(window -> getMVP() -> getModel(), glm::radians(0.2f), glm::vec3(0,1,0)));
    GLuint MatrixID = glGetUniformLocation(window -> getShaderID(), "model_matrix");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(window -> getMVP() -> getModel()[0][0]));
}

void key_press_e(Window* window)
{
    //when the n key is pressed, the OBJECT itself (not the camera) should be rotated about the z-axis.
    //in order to do this, we want to modify the Model matrix
    window -> getMVP() -> setModel(glm::rotate(window -> getMVP() -> getModel(), glm::radians(1.5f), glm::vec3(0,0,1)));
    GLuint MatrixID = glGetUniformLocation(window -> getShaderID(), "model_matrix");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(window -> getMVP() -> getModel()[0][0]));
}

void key_press_j(Window* window)
{
    //when the j key is pressed, the OBJECT itself (not the camera) should be translated along the x axis
    //in the positive direction
    //in order to do this, we want to modify the Model matrix
    window -> getMVP() -> setModel(glm::translate(window -> getMVP() -> getModel(), glm::vec3(0.2f, 0 , 0))) ;
    GLuint MatrixID = glGetUniformLocation(window -> getShaderID(), "model_matrix");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(window -> getMVP() -> getModel()[0][0]));
}

void key_press_l(Window* window)
{
    //when the l key is pressed, the OBJECT itself (not the camera) should be translated along the x axis
    //in the positive direction
    //in order to do this, we want to modify the Model matrix
    window -> getMVP() -> setModel(glm::translate(window -> getMVP() -> getModel(), glm::vec3(-0.2f, 0 , 0))) ;
    GLuint MatrixID = glGetUniformLocation(window -> getShaderID(), "model_matrix");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(window -> getMVP() -> getModel()[0][0]));
}

void key_press_i(Window* window)
{
    //when the i key is pressed, the OBJECT itself (not the camera) should be translated along the y axis
    //in the positive direction
    //in order to do this, we want to modify the Model matrix
    window -> getMVP() -> setModel(glm::translate(window -> getMVP() -> getModel(), glm::vec3(0, 0.2f , 0))) ;
    GLuint MatrixID = glGetUniformLocation(window -> getShaderID(), "model_matrix");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(window -> getMVP() -> getModel()[0][0]));
}

void key_press_k(Window* window)
{
    //when the k key is pressed, the OBJECT itself (not the camera) should be translated along the y axis
    //in the negative direction
    //in order to do this, we want to modify the Model matrix
    window -> getMVP() -> setModel(glm::translate(window -> getMVP() -> getModel(), glm::vec3(0, -0.2f , 0))) ;
    GLuint MatrixID = glGetUniformLocation(window -> getShaderID(), "model_matrix");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(window -> getMVP() -> getModel()[0][0]));
}

void key_press_pg_up(Window* window)
{
    //when the page up key is pressed, the OBJECT itself (not the camera) should be translated along the z axis
    //in the positive direction
    //in order to do this, we want to modify the Model matrix
    window -> getMVP() -> setModel(glm::translate(window -> getMVP() -> getModel(), glm::vec3(0, 0 , 0.2f))) ;
    GLuint MatrixID = glGetUniformLocation(window -> getShaderID(), "model_matrix");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(window -> getMVP() -> getModel()[0][0]));
}

void key_press_pg_down(Window* window)
{
    //when the page down key is pressed, the OBJECT itself (not the camera) should be translated along the z axis
    //in the negative direction
    //in order to do this, we want to modify the Model matrix
    window -> getMVP() -> setModel(glm::translate(window -> getMVP() -> getModel(), glm::vec3(0, 0 , -0.2f))) ;
    GLuint MatrixID = glGetUniformLocation(window -> getShaderID(), "model_matrix");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(window -> getMVP() -> getModel()[0][0]));
}

void key_press_1(Window* window)
{
    //when this key is pressed, we first need to find the id of the red channel uniform in the shader program
    GLuint red_channel_id = glGetUniformLocation(window -> getShaderID(), "red_channel");
    GLfloat red_val; //this will hold the current value of the red channel uniform in the shader program
    glGetUniformfv(window -> getShaderID(), red_channel_id, &red_val); //this will change the value of red_val so we have the
                                                          //the current one
    if(red_val == 1.0f)
        glUniform1f(red_channel_id, 0.0f);
    else
        glUniform1f(red_channel_id, 1.0f);

    //this changes the value of the red_channel from 1 to 0 or zero to 1 depending on what the current value is
}

void key_press_2(Window* window)
{
    //this method works exactly in the same way as the one for the red channel, the only difference is that here
    //we are modifying the green channel's value

    GLuint green_channel_id = glGetUniformLocation(window -> getShaderID(), "green_channel");
    GLfloat green_val;
    glGetUniformfv(window -> getShaderID(), green_channel_id, &green_val);

    if(green_val == 1.0f)
        glUniform1f(green_channel_id, 0.0f);
    else
        glUniform1f(green_channel_id, 1.0f);
}

void key_press_3(Window* window)
{
    //this method works exactly in the same way as the one for the red channel, the only difference is that here
    //we are modifying the blue channel's value

    GLuint blue_channel_id = glGetUniformLocation(window -> getShaderID(), "blue_channel");
    GLfloat blue_val;
    glGetUniformfv(window -> getShaderID(), blue_channel_id, &blue_val);

    if(blue_val == 1.0f)
        glUniform1f(blue_channel_id, 0.0f);
    else
        glUniform1f(blue_channel_id, 1.0f);
}

void key_press_4(Window* window)
{
    //when the '4' key is pressed on the keyboard, all of the channels should be toggled on.
    //to do this, we need to first find all of our channels
    GLuint red_channel_id = glGetUniformLocation(window -> getShaderID(), "red_channel");
    GLuint green_channel_id = glGetUniformLocation(window -> getShaderID(), "green_channel");
    GLuint blue_channel_id = glGetUniformLocation(window -> getShaderID(), "blue_channel");

    //now that we have the color id's we need to change their values
    glUniform1f(red_channel_id, 1.0f);
    glUniform1f(green_channel_id, 1.0f);
    glUniform1f(blue_channel_id, 1.0f);
}

void key_press_6(Window* window)
{
    //if the light is on, then we should turn it off and vice versa
    GLuint light_on_id = glGetUniformLocation(window -> getShaderID(), "light_on");
    GLint light_on_value;
    glGetUniformiv(window -> getShaderID(), light_on_id, &light_on_value);

    if(light_on_value == 1)
        glUniform1i(light_on_id, 0);
    else
        glUniform1i(light_on_id, 1);
}

void key_press_5(Window* window, GLboolean& gouraud)
{
    //there are two cases, either gouraud is true, in which case, we should switch the value of the uniform for gouraud
    //it is false, and we should load the gouraud shaders and flip it.
    if(gouraud)
    {
        std::cout << "Switching to Phong Illumination Model..." << std::endl;
        GLuint gouraudUsed = glGetUniformLocation(window -> getShaderID(), "gouraudUsed");
        glUniform1i(gouraudUsed, 0);
        gouraud = GL_FALSE;
    }

    else
    {
        std::cout << "Switching to Gouraud Illumination Model..." << std::endl;
        GLuint gouraudUsed = glGetUniformLocation(window -> getShaderID(), "gouraudUsed");
        glUniform1i(gouraudUsed, 1);
        gouraud = GL_TRUE;
    }
}

void key_press_m(Window* window)
{
    //first we must check the value of the uniform
    GLint flag_value;
    glGetUniformiv(window -> getShaderID(), glGetUniformLocation(window -> getShaderID(), "normal_as_color"), &flag_value);

    //now that we have the current value, we should flip it
    if(flag_value == 1)
    {
        GLuint flag_location = glGetUniformLocation(window -> getShaderID(), "normal_as_color");
        glUniform1i(flag_location, 0);
    }

    else
    {
        GLuint flag_location = glGetUniformLocation(window -> getShaderID(), "normal_as_color");
        glUniform1i(flag_location, 1);
    }
}

void key_press_g(Window* window)
{
    //first we must check the value of the uniform
    GLint flag_value;
    glGetUniformiv(window -> getShaderID(), glGetUniformLocation(window -> getShaderID(), "gray_scale"), &flag_value);

    //now that we have the current value, we should flip it
    if(flag_value == 1)
    {
        GLuint flag_location = glGetUniformLocation(window -> getShaderID(), "gray_scale");
        glUniform1i(flag_location, 0);
    }

    else
    {
        GLuint flag_location = glGetUniformLocation(window -> getShaderID(), "gray_scale");
        glUniform1i(flag_location, 1);
    }
}

void key_press_F1(Window* window, GLboolean& lights_on)
{
    //when the F1 key is pressed, it should toggle between the scene having the 4 lights or only one
    //in order to do this, we can
    if(lights_on)
    {
        //if the lights are on, we should make all of them dark except the first light and change its color
        //and position to match the definition in part B

        glUniform3fv(glGetUniformLocation(window -> getShaderID(), "light_position_1"), 1, glm::value_ptr(glm::vec3(0,20,10)));
        glUniform3fv(glGetUniformLocation(window -> getShaderID(), "light_color_1"), 1, glm::value_ptr(glm::vec3(0.8,0.2,0.2)));
        glUniform3fv(glGetUniformLocation(window -> getShaderID(), "light_color_2"), 1, glm::value_ptr(glm::vec3(0,0,0)));
        glUniform3fv(glGetUniformLocation(window -> getShaderID(), "light_color_3"), 1, glm::value_ptr(glm::vec3(0,0,0)));
        glUniform3fv(glGetUniformLocation(window -> getShaderID(), "light_color_4"), 1, glm::value_ptr(glm::vec3(0,0,0)));
        lights_on = GL_FALSE;
    }

    else
    {
        glUniform3fv(glGetUniformLocation(window -> getShaderID(), "light_position_1"), 1, glm::value_ptr(glm::vec3(10,15,5)));
        glUniform3fv(glGetUniformLocation(window -> getShaderID(), "light_color_1"), 1, glm::value_ptr(glm::vec3(0.2,0.05,0.05)));
        glUniform3fv(glGetUniformLocation(window -> getShaderID(), "light_color_2"), 1, glm::value_ptr(glm::vec3(0.05,0.2,0.05)));
        glUniform3fv(glGetUniformLocation(window -> getShaderID(), "light_color_3"), 1, glm::value_ptr(glm::vec3(0.05,0.05,0.2)));
        glUniform3fv(glGetUniformLocation(window -> getShaderID(), "light_color_4"), 1, glm::value_ptr(glm::vec3(0.05,0.05,0.05)));
        lights_on = GL_TRUE;
    }
}

void key_press_F2(Window* window)
{
    //first make sure only one light is being used (the one in the assignment description)
    glUniform3fv(glGetUniformLocation(window -> getShaderID(), "light_position_1"), 1, glm::value_ptr(glm::vec3(0,20,10)));
    glUniform3fv(glGetUniformLocation(window -> getShaderID(), "light_color_1"), 1, glm::value_ptr(glm::vec3(0.8,0.2,0.2)));
    glUniform3fv(glGetUniformLocation(window -> getShaderID(), "light_color_2"), 1, glm::value_ptr(glm::vec3(0,0,0)));
    glUniform3fv(glGetUniformLocation(window -> getShaderID(), "light_color_3"), 1, glm::value_ptr(glm::vec3(0,0,0)));
    glUniform3fv(glGetUniformLocation(window -> getShaderID(), "light_color_4"), 1, glm::value_ptr(glm::vec3(0,0,0)));
}