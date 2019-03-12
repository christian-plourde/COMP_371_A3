#include "MouseControls.h"

void key_press_rm_button_down(Window* window)
{
    window -> getMVP() -> setView(glm::translate(window -> getMVP() -> getView(), glm::vec3(0,0,0.1)));
    GLuint MatrixID = glGetUniformLocation(window -> getShaderID(), "view_matrix");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(window -> getMVP() -> getView()[0][0]));
}

void key_press_lm_button_down(Window* window)
{
    window -> getMVP() -> setView(glm::translate(window -> getMVP() -> getView(), glm::vec3(0,0,-0.1)));
    GLuint MatrixID = glGetUniformLocation(window -> getShaderID(), "view_matrix");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(window -> getMVP() -> getView()[0][0]));
}