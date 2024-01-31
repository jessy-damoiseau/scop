#ifndef INPUT_HPP
#define INPUT_HPP

#include <header.hpp>
#include <math4/math4.hpp>

class Input {
    public:
        Input();
        ~Input();
        
        void checkInput(GLFWwindow *window);
        matrix4 createTransform();

        bool getIsColor() const;

    private:
        float _fov;
        float _x;
        float _y;
        float _z;
        float _xrot;
        float _yrot;
        float _zrot;
        bool _isColor;
        bool _C_PRESS;


};

#endif