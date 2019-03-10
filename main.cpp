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

//definition of all the uniforms
GLint view_mat_ID;
GLint model_mat_ID;
GLint projection_mat_ID;
glm::mat4 Model;
glm::mat4 Projection;
glm::mat4 View;
GLint red_channel_id;
GLint blue_channel_id;
GLint green_channel_id;
GLint light_position_1;
GLint light_color_1;
GLint light_position_2;
GLint light_color_2;
GLint light_position_3;
GLint light_color_3;
GLint light_position_4;
GLint light_color_4;
GLint view_position;

//definition of the buffers
GLuint vertexBuffer;
GLuint normalBuffer;
std::vector<glm::vec3> vertices, normals;
std::vector<glm::vec2> uvs;
std::vector<int> indices; //this will hold the indices for the EBO
GLuint FloorVertexArrayID; //this is our reference to our vao
GLuint FloorVertexBuffer;
GLuint FloorNormalBuffer;
std::vector<glm::vec3> floor_vertices, floor_normals;
std::vector<glm::vec2> floor_uvs;
std::vector<int> floor_indices; //this will hold the indices for the EBO
GLFWwindow* window;
double oldMouseY = 0;
double newMouseY = 0;

//more uniform definitions
GLboolean four_lights_on;
GLint lightOn; //a flag to determine whether or not the light should be on (1 is on, 0 is off)
GLboolean gouraud_flag; //this determines if we use gouraud or not (alternative is phong) for lighting
GLint gouraudUsed; //will be used as a flag to determine which shading should be used.
GLint normal_as_color; //this is a flag to determine if the normal should be used as color (M key toggles on/off)
GLint gray_scale; //this is a flag to determine if the scene should be rendered in grayscale or not (key G)
GLuint depthMapProgramID; //the id for the shader program used to render the depth map
GLuint programID; //this variable will be assigned the program ID of the shader program
                  //since we need it to modify the color channels, we will make it global
                  //so we can use it in the keyboard callback method

/*
 * Method to reset the values of all the uniforms for the new program id when we switch shaders.
 */
void setUniforms()
{
    //first we get handles for all of the matrix uniforms to use in our MVP matrix and we set their values
    //according to the matrices defined in the main method
    view_mat_ID = glGetUniformLocation(programID, "view_matrix");
    model_mat_ID = glGetUniformLocation(programID, "model_matrix");
    projection_mat_ID = glGetUniformLocation(programID, "projection_matrix");
    glUniformMatrix4fv(view_mat_ID, 1, GL_FALSE, &View[0][0]);
    glUniformMatrix4fv(model_mat_ID, 1, GL_FALSE, &Model[0][0]);
    glUniformMatrix4fv(projection_mat_ID, 1, GL_FALSE, &Projection[0][0]);

    //next we need to set up three uniforms, one for each color channel since we will be implementing controls
    //to toggle each one on and off.
    red_channel_id = glGetUniformLocation(programID, "red_channel");
    glUniform1f(red_channel_id, 1.0f);
    green_channel_id = glGetUniformLocation(programID, "green_channel");
    glUniform1f(green_channel_id, 1.0f);
    blue_channel_id = glGetUniformLocation(programID, "blue_channel");
    glUniform1f(blue_channel_id, 1.0f);

    //next is a uniform to turn on and off the light as a whole. (No light means no lighting model is used)
    lightOn = glGetUniformLocation(programID, "light_on");
    glUniform1i(lightOn, 1);

    //we also need to set the flag to determine if the normal should be used as the color
    normal_as_color = glGetUniformLocation(programID, "normal_as_color");
    glUniform1i(normal_as_color, 0);

    //we also need to set the flag to determine if the scene should be rendered in grayscale or not
    //initially it will be set to not do it in grayscale.
    gray_scale = glGetUniformLocation(programID, "gray_scale");
    glUniform1i(gray_scale, 0);

    //this is the view position of the camera. This is important for calculating the impact of the specular light
    //component.
    view_position = glGetUniformLocation(programID, "view_position");
    glUniform3fv(view_position, 1, glm::value_ptr(glm::vec3(100,100,100)));

    //these are the uniforms that define the position of the lights
    light_position_1 = glGetUniformLocation(programID, "light_position_1");
    glUniform3fv(light_position_1, 1, glm::value_ptr(glm::vec3(0, 20, 10)));

    light_position_2 = glGetUniformLocation(programID, "light_position_2");
    glUniform3fv(light_position_2, 1, glm::value_ptr(glm::vec3(-10, 15, 5)));

    light_position_3 = glGetUniformLocation(programID, "light_position_3");
    glUniform3fv(light_position_3, 1, glm::value_ptr(glm::vec3(0, 15, 5)));

    light_position_4 = glGetUniformLocation(programID, "light_position_4");
    glUniform3fv(light_position_4, 1, glm::value_ptr(glm::vec3(0, 0, 25)));

    //these are the uniforms that define the colors of the lights
    light_color_1 = glGetUniformLocation(programID, "light_color_1");
    glUniform3fv(light_color_1, 1, glm::value_ptr(glm::vec3(0.8,0.2,0.2)));

    light_color_2 = glGetUniformLocation(programID, "light_color_2");
    glUniform3fv(light_color_2, 1, glm::value_ptr(glm::vec3(0,0,0)));

    light_color_3 = glGetUniformLocation(programID, "light_color_3");
    glUniform3fv(light_color_3, 1, glm::value_ptr(glm::vec3(0,0,0)));

    light_color_4 = glGetUniformLocation(programID, "light_color_4");
    glUniform3fv(light_color_4, 1, glm::value_ptr(glm::vec3(0,0,0)));

    gouraudUsed = glGetUniformLocation(programID, "gouraudUsed");
    glUniform1i(gouraudUsed, 0);

}

/*
 * This is the method that will execute when there is input from the keyboard.
 * For this method to be a valid callback method for the keyboard, it must match the proper signature,
 * which is the one used for this method.
 */
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
        key_press_w(window, View, Projection, Model, programID);

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        key_press_s(window, View, Projection, Model, programID);

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        key_press_a(window, View, Projection, Model, programID);

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        key_press_d(window, View, Projection, Model, programID);

    if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        key_press_o(window, View, Projection, Model, programID);

    if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        key_press_p(window, View, Projection, Model, programID);

    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        key_press_left_arrow(window, View, Projection, Model, programID);

    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        key_press_right_arrow(window, View, Projection, Model, programID);

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        key_press_up_arrow(window, View, Projection, Model, programID);

    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        key_press_down_arrow(window, View, Projection, Model, programID);

    if(glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
        key_press_b(window, View, Projection, Model, programID);

    if(glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        key_press_n(window, View, Projection, Model, programID);

    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        key_press_e(window, View, Projection, Model, programID);

    if(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        key_press_j(window, View, Projection, Model, programID);

    if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        key_press_l(window, View, Projection, Model, programID);

    if(glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        key_press_i(window, View, Projection, Model, programID);

    if(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        key_press_k(window, View, Projection, Model, programID);

    if(glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
        key_press_pg_up(window, View, Projection, Model, programID);

    if(glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
        key_press_pg_down(window, View, Projection, Model, programID);

    //controls what occurs when the '1' key is pressed
    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        key_press_1(programID);

    //controls what happens when the '2' key is pressed
    if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        key_press_2(programID);

    //controls what happens when the '3' key is pressed
    if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        key_press_3(programID);

    if(glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        key_press_4(programID);

    if(glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
        key_press_6(programID);

    if(glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        key_press_5(programID, gouraud_flag);
    }

    if(glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        key_press_m(programID);

    if(glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        key_press_g(programID);

    if(glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
        key_press_F1(programID, four_lights_on);

    if(glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
        key_press_F2(programID);
}

/*
 * Method to handle the initialization process of the window
 */
static GLFWwindow* initialize()
{
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
        return nullptr;

    // Create a windowed mode window and its OpenGL context
    int width =  800;
    int height = 800;
    window = glfwCreateWindow(width, height, "COMP 371 A3", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return nullptr;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    glClearColor(0.8, 0.8, 0.8, 1); //makes the background color of the window light gray
    //we should also set the keyboard input callback method
    glfwSetKeyCallback(window, keyboard_callback);
    glfwWindowHint(GLFW_DOUBLEBUFFER, 1);

    glewExperimental = GL_TRUE;

    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return nullptr;
    }

    four_lights_on = GL_FALSE; //toggle mechanism for the f1 key being pressed.

    return window;
}

/*
 * Method used to render the scene
 */
void Render()
{
    // Render here
    //each time we draw we should clear both the color and the depth buffer bit so that the sorting process can
    //begin again from scratch
    //if we don't clear the depth buffer, then on the next frame everything we want to draw will be further than the
    //last closest item (obviously) and we won't have anything drawn
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //DRAWING HERACLES

    //to do this we need to tell open GL about our vertex array (id 0)
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    //we also need to enable the normals array
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    //this configures the z-buffer so that only elements that are closer will be drawn
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //here we need to specify the number of vertices we wish to draw
    //for this assignment, they should be drawn using triangles
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << std::endl;
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    //HERACLES DRAWING COMPLETE

    //DRAWING CUBES
    //now that we have drawn Heracles, we should switch to our cube VAO
    glBindVertexArray(FloorVertexArrayID);
    //to do this we need to tell open GL about our vertex array (id 0)
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, FloorVertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    //we also need to enable the normals array
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, FloorNormalBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, floor_vertices.size());
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    //CUBE DRAWING COMPLETE

    // Swap front and back buffers
    glfwSwapBuffers(window);

    //check if there was input
    //this includes clicking the close button on the window
    glfwPollEvents();

    //before dealing with the mouse input, we need to get the current position of the mouse and compare it to
    //the old. Since we don't care about x, we can just pass 0.
    glfwGetCursorPos(window, &newMouseY, 0);

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && newMouseY > oldMouseY)
        key_press_lm_button_up(window, View, Projection, Model, programID);

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && newMouseY < oldMouseY)
        key_press_lm_button_down(window, View, Projection, Model, programID);

    //update the last position of the mouse
    oldMouseY = newMouseY;
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
    float near_plane = 0.0f, far_plane = 100.0f;
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);

    glm::mat4 lightView = glm::lookAt(glm::vec3(0,20,10), glm::vec3(0,0,0), glm::vec3(0,0,0));

    glm::mat4 lightSpaceMatrix = lightProjection * lightView;
    glUniform4fv(glGetUniformLocation(programID, "light_matrix"), 1, glm::value_ptr(lightSpaceMatrix));
}

int main()
{
    std::cout << glfwGetVersionString() << std::endl;
    window = initialize();

    if(window == nullptr)
    {
        std::cout << "ERROR -- Initialization failed." << std::endl;
        return -1;
    }

    /************************************************ HERACLES LOADING *****************************************/

    //we need to load the data for the object that we would like to draw from an object file
    //we can do this using the method that we have defined


    //we try to load the object file and if we fail, then we simply exit the program since we won't be able to draw anything
    if(!LoadOBJ("../ObjectFiles/heracles.obj",indices, vertices, normals, uvs))
        return -1;

    GLuint VertexArrayID; //this is our reference to our vao
    glGenVertexArrays(1, &VertexArrayID); //this will generate the actual array for us and we want only one
    glBindVertexArray(VertexArrayID); //then we make it the current one (pass to GPU)

    //Now in order for openGL to be able to draw this triangle we need to pass it then data by creating a vertex buffer
    //object
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertices.size(), &vertices.front(), GL_STATIC_DRAW);

    //for the lighting, we also need the normals, therefore we should create another vbo

    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*normals.size(), &normals.front(), GL_STATIC_DRAW);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indices.size(), &indices.front(), GL_STATIC_DRAW);

    /************************************************ DONE HERACLES LOADING *****************************************/

    /************************************************ FLOOR LOADING *****************************************/
    //we will also need to load a floor in order to implement the shadows

    //we try to load the object file and if we fail, then we simply exit the program since we won't be able to draw anything
    if(!LoadOBJ("../ObjectFiles/floor.obj",floor_indices, floor_vertices, floor_normals, floor_uvs))
        return -1;


    glGenVertexArrays(1, &FloorVertexArrayID); //this will generate the actual array for us and we want only one
    glBindVertexArray(FloorVertexArrayID); //then we make it the current one (pass to GPU)

    //Now in order for openGL to be able to draw this triangle we need to pass it then data by creating a vertex buffer
    //object
    glGenBuffers(1, &FloorVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, FloorVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*floor_vertices.size(), &floor_vertices.front(), GL_STATIC_DRAW);

    //for the lighting, we also need the normals, therefore we should create another vbo
    glGenBuffers(1, &FloorNormalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, FloorNormalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*floor_normals.size(), &floor_normals.front(), GL_STATIC_DRAW);

    GLuint FloorEBO;
    glGenBuffers(1, &FloorEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, FloorEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*floor_indices.size(), &floor_indices.front(), GL_STATIC_DRAW);

    /************************************************ FLOOR LOADING *****************************************/

    /******************************************* DEPTH MAP DEFINITION ****************************************/

    GLuint depthBuffer;
    glGenFramebuffers(1, &depthBuffer);

    const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    GLuint depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindFramebuffer(GL_FRAMEBUFFER, depthBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    /****************************************** END DEPTH MAP DEFINITION *************************************/

    /************************************* SHADER LOADING ***************************************************/
    //now we load the shader program and assign it to our program id
    //initially, we use the Phong illumination model
    gouraud_flag = GL_FALSE;
    programID = LoadShaders("../Shaders/VertexShader.glsl", "../Shaders/FragmentShader.glsl");
    glUseProgram(programID);

    //we should also load the depth map shader set
    depthMapProgramID = LoadShaders("../Shaders/DepthMapVertexShader.glsl", "../Shaders/DepthMapFragmentShader.glsl");

    /************************************* DONE SHADER LOADING ***************************************************/

    /************************************* MODEL VIEW PROJECTION INSTANTIATION **************************************/
    //in order for this object to be viewed from a perspective view, we need a Model View Projection matrix
    //we wish to draw the triangle from a perspective view
    //this is the projection matrix for a perspective view
    int width; //the width of the window
    int height; //the height of the window
    glfwGetWindowSize(window, &width, &height);

    //this creates an perspective projection matrix which we will use to render our object
    Projection = glm::perspective(glm::radians(45.0f), (float)width/height, 0.1f, 200.0f);
    //we then need a camera matrix, we will make it look at the origin
    View = glm::lookAt(glm::vec3(0,0,-40),glm::vec3(0,0,0), glm::vec3(0, 1, 0));

    //this is the model matrix (the identity matrix since we are placing the mode (our triangle) at the origin.
    //also changing this will modify what the final triangle looks like. This is where we apply transformations
    //such as scaling, translation, etc.
    Model = glm::mat4(1.0f);

    //now that we have our matrices, we should set all of our uniforms
    setUniforms();

    /************************************* DONE MODEL VIEW PROJECTION INSTANTIATION ******************************/

    //we need to define two doubles to hold the old and new positions of the mouse cursor so we can check
    //which direction the user is moving the mouse in.

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        //first pass, in which we render to the depth map
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthBuffer);
        glClear(GL_DEPTH_BUFFER_BIT);
        DepthMapPass();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        //once we are done with this, we should switch back to our actual program
        glUseProgram(programID);

        //second pass where we actually render the scene
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        Render();

    }

    glfwTerminate();

    return 0;
}