Author: Christian Plourde
Student ID: 26572499

This program loads in a heracles object file as well as a floor and allows the user to view it and interact with the
model by using the mouse and keyboard inputs listed below.

This program consists of a main function, found within the main.cpp file, as well as one set of shaders.
The keyboard control functions are defined in the KeyboardControls.h file and implemented in the KeyboardControls.cpp
file. The file used to generate the model of heracles is found in the heracles.obj file and the loader function to load
it from the file is found in the ObjectLoader.cpp file (the implementation of the function defined in the ObjectLoader.h
file). Finally the shader compiler is found in the ShaderLoader.h file (and implemented in the ShaderLoader.cpp file).

The keyboard controls are as follows:
Left-Mouse-Button + Mouse Up = Move into the scene
Left-Mouse-Button + Mouse Down = Move out of the scene
W = Move camera in negative Z direction
S = Move camera in positive Z direction
A = Move camera in negative X direction
D = Move camera in positive X direction
O = Scale the object up by a factor of 10%
P = Scale the object down by a factor of 10%
Left-Arrow = Rotate the camera counterclockwise around the up vector
Right-Arrow = Rotate the camera clockwise around the up vector
Up-Arrow = Rotate the camera counterclockwise around the right vector
Down-Arrow = Rotate the camera clockwise around the right vector
B = Rotate the objects around the x-axis in counterclockwise fashion
N = Rotate the objects around the y-axis in counterclockwise fashion
E = Rotate the objects around the z-axis in counterclockwise fashion
J = Translate the objects along the negative x-axis
L = Translate the objects along the positive x-axis
I = Translate the objects along the positive y-axis
K = Translate the objects along the negative y-axis
Page Up = Translate the objects along the positive z-axis
Page Down = Translate the objects along the negative z-axis
1 = Toggle on/off the red color channel
2 = Toggle on/off the green color channel
3 = Toggle on/off the blue color channel
4 = Turn all the color channels to max (1.0f)
5 = Toggle between Gouraud and Phong Illumination models.
6 = Toggle between the currently selected illumination model and no illumination model.
M = Toggles the use of the normal as the color of each vertex/fragment.
G = Toggles between grayscale or color rendering of the scene.
F1 = Set the scene with four lights.
F2 = Use Two-Pass Shadow Mapping with one light source.






