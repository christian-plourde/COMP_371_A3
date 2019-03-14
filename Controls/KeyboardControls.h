#ifndef COMP_371_A1_KEYBOARDCONTROLS_H
#define COMP_371_A1_KEYBOARDCONTROLS_H
#endif

#include <glew.h>
#include <GLFW/glfw3.h>
#include "../GLM/glm/matrix.hpp"
#include "../GLM/glm/gtc/matrix_transform.hpp"
#include "../Utilities/Window.h"

/*
 * This method defines what occurs when the w key is pressed on the keyboard. For this assignment, it modifies
 * the viewing angle of the camera and so to change this, we need to pass in the View, Projection, and Model
 * matrices, as well as the shader ID since we will need to update the value in the uniform in the shader program
 * once we have recalculated the location of the camera.
 */
void key_press_w(Window*);

/*
 * This method defines what occurs when the s key is pressed on the keyboard. For this assignment, it modifies
 * the viewing angle of the camera and so to change this, we need to pass in the View, Projection, and Model
 * matrices, as well as the shader ID since we will need to update the value in the uniform in the shader program
 * once we have recalculated the location of the camera.
 */
void key_press_s(Window*);

/*
 * This method defines what occurs when the a key is pressed on the keyboard. For this assignment, it modifies
 * the viewing angle of the camera and so to change this, we need to pass in the View, Projection, and Model
 * matrices, as well as the shader ID since we will need to update the value in the uniform in the shader program
 * once we have recalculated the location of the camera.
 */
void key_press_a(Window*);

/*
 * This method defines what occurs when the d key is pressed on the keyboard. For this assignment, it modifies
 * the viewing angle of the camera and so to change this, we need to pass in the View, Projection, and Model
 * matrices, as well as the shader ID since we will need to update the value in the uniform in the shader program
 * once we have recalculated the location of the camera.
 */
void key_press_d(Window*);

/*
 * This method defines what occurs when the o key is pressed on the keyboard. For this assignment, it modifies
 * the size uniformly of the object and so to change this, we need to pass in the View, Projection, and Model
 * matrices, as well as the shader ID since we will need to update the value in the uniform in the shader program
 * once we have recalculated the size of the model.
 */
void key_press_o(Window*);

/*
 * This method defines what occurs when the p key is pressed on the keyboard. For this assignment, it modifies
 * the size uniformly of the object and so to change this, we need to pass in the View, Projection, and Model
 * matrices, as well as the shader ID since we will need to update the value in the uniform in the shader program
 * once we have recalculated the size of the model.
 */
void key_press_p(Window*);

/*
 * This method defines what occurs when the left arrow key is pressed on the keyboard. When this occurs, the camera
 * should rotate counterclockwise about the up vector.
 */
void key_press_left_arrow(Window*);

/*
 * This method defines what occurs when the right arrow key is pressed on the keyboard. When this occurs, the camera
 * should rotate clockwise about the up vector.
 */
void key_press_right_arrow(Window*);

/*
 * This method defines what occurs when the up arrow key is pressed on the keyboard. When this occurs, the camera
 * should rotate counterclockwise about the right vector.
 */
void key_press_up_arrow(Window*);

/*
 * This method defines what occurs when the down arrow key is pressed on the keyboard. When this occurs, the camera
 * should rotate clockwise about the right vector.
 */
void key_press_down_arrow(Window*);

/*
 * This method defined what happens when b is pressed on the keyboard. When this occurs, the OBJECT (i.e. the model)
 * will be rotated about the x axis in counterclockwise fashion
 */
void key_press_b(Window*);

/*
 * This method defined what happens when n is pressed on the keyboard. When this occurs, the OBJECT (i.e. the model)
 * will be rotated about the y axis in counterclockwise fashion
 */
void key_press_n(Window*);

/*
 * This method defined what happens when e is pressed on the keyboard. When this occurs, the OBJECT (i.e. the model)
 * will be rotated about the z axis in counterclockwise fashion
 */
void key_press_e(Window*);

/*
 * This method defined what happens when j is pressed on the keyboard. When this occurs, the OBJECT (i.e. the model)
 * will be translated along the x axis in the positive direction
 */
void key_press_j(Window*);

/*
 * This method defined what happens when l is pressed on the keyboard. When this occurs, the OBJECT (i.e. the model)
 * will be translated along the x axis in the negative direction
 */
void key_press_l(Window*);

/*
 * This method defined what happens when i is pressed on the keyboard. When this occurs, the OBJECT (i.e. the model)
 * will be translated along the y axis in the positive direction
 */
void key_press_i(Window*);

/*
 * This method defined what happens when k is pressed on the keyboard. When this occurs, the OBJECT (i.e. the model)
 * will be translated along the y axis in the negative direction
 */
void key_press_k(Window*);

/*
 * This method defined what happens when page up is pressed on the keyboard. When this occurs, the OBJECT (i.e. the model)
 * will be translated along the z axis in the positive direction
 */
void key_press_pg_up(Window*);

/*
 * This method defines what happens when page down is pressed on the keyboard. When this occurs, the OBJECT (i.e. the model)
 * will be translated along the z axis in the negative direction
 */
void key_press_pg_down(Window*);

/*
 * This method defines what happens when the 'm' key is pressed. When this occurs, the normal_as_color uniform should
 * be toggled between 0 and 1, to determine if the normal should be used as the fragment color or not.
 */
void key_press_m(Window*);

/*
 * This method defines what happens when the 'g' key is pressed. When this occurs, it should toggle between grayscale
 * rendering mode by flipping the flag in the shader program.
 */
void key_press_g(Window*);

/*
 * This defines what happens when the 'F1' key is pressed. When this occurs, the 4 lights in the scene should be
 * enabled. If the key has not been pressed, then there should only be one light on the scene.
 */
void key_press_F1(Window*);

/*
 * This defines what occurs when the 'F2' key is pressed. When this occurs, we should render the scene with two-pass
 * shadow mapping. Also, before doing anything, we should set the scene with only the one light.
 */
void key_press_F2(Window*);