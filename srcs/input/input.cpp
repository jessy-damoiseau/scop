#include <input/input.hpp>

Input::Input(){
    this->_fov = 45.0f;
    this->_x = 0.0f;
    this->_y = 0.0f;
    this->_z = -5.0f;
    this->_xrot = 0.0f;
    this->_yrot = 0.0f;
    this->_zrot = 0.0f;
    this->_isColor = true;
    this->_C_PRESS = false;

}

Input::~Input(){
}

void Input::checkInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        this->_fov += 0.1f;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        this->_fov -= 0.1f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        this->_x -= 0.1f;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        this->_x += 0.1f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        this->_y += 0.1f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        this->_y -= 0.1f;
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        this->_z += 0.1f;
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        this->_z -= 0.1f;
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        this->_fov = 45.0f;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        this->_xrot -= 0.1f;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        this->_xrot += 0.1f;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        this->_yrot -= 0.1f;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        this->_yrot += 0.1f;
    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
        this->_zrot -= 0.1f;
    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
        this->_zrot += 0.1f;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && !_C_PRESS){
        if (!_C_PRESS)
            this->_isColor = !this->_isColor;
        _C_PRESS = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE && _C_PRESS){
        _C_PRESS = false;
    }
}
    
matrix4 Input::createTransform(){
    matrix4 proj = matrix4().perspective(this->_fov, (float)1280/(float)920, 0.1f, 100.0f);
    matrix4 transform = matrix4(1.0f);
    matrix4 rotatey = matrix4(1.0f);
    matrix4 rotatex = matrix4(1.0f);
    matrix4 rotatez = matrix4(1.0f);
    rotatey = rotatey.rotate(this->_yrot, 0.0f, 1.0f, 0.0f);
    rotatex = rotatex.rotate(this->_xrot, 1.0f, 0.0f, 0.0f);
    rotatez = rotatez.rotate(this->_zrot, 0.0f, 0.0f, 1.0f);
    // rotatez = rotatez.rotate((float)glfwGetTime(), 0.0f, 0.0f, 1.0f);
    transform = transform.translate(this->_x, this->_y, this->_z);
    transform = proj * transform * rotatey * rotatex * rotatez;
    return transform;
}

bool Input::getIsColor() const
{
    return this->_isColor;
}
