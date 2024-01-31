#ifndef MATH4_HPP
#define MATH4_HPP

#include <cmath>

class matrix4 {
    public:
        matrix4();
        ~matrix4();

        matrix4(float);
        matrix4(const matrix4&);

        matrix4& operator=(const matrix4&);
        float* operator[](int);

        matrix4 operator*(const matrix4&);

        matrix4& translate(float, float, float);
        matrix4& rotate(float, float, float, float);
        matrix4& perspective(float, float, float, float);

        float* get_value();

    private:
        float _value[4][4];

};

#endif
