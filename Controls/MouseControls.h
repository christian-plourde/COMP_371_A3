#ifndef MOUSE_CONTROLS_H
#define MOUSE_CONTROLS_H
#endif

#include <glew.h>
#include <GLFW/glfw3.h>
#include "../GLM/glm/matrix.hpp"
#include "../GLM/glm/gtc/matrix_transform.hpp"
#include "../Utilities/Window.h"

/*
 * This method defines what happens when the left mouse button is pressed. This should move the camera in and out of
 * the scene. If the mouse is moved up while the left button is clicked, then the camera should move in. Down should
 * make the camera move out of the scene.
 */
void key_press_lm_button_down(Window*);

/*
 * This method defines what happens when the left mouse button is pressed. This should move the camera in and out of
 * the scene. If the mouse is moved up while the left button is clicked, then the camera should move in. Down should
 * make the camera move out of the scene.
 */
void key_press_rm_button_down(Window*);