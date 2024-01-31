#include <math4/math4.hpp>

matrix4::matrix4(float value) {
    for (int i = 0; i < 4; i++)
		for (int y = 0; y < 4; y++)
			this->_value[i][y] = 0;
    for (int i = 0; i < 4; i++) {
        _value[i][i] = value;
    }
}

matrix4::matrix4() {
    for (int i = 0; i < 4; i++)
		for (int y = 0; y < 4; y++)
			this->_value[i][y] = 0;
}

matrix4::~matrix4() {}

matrix4::matrix4(const matrix4& other) {
    *this = other;
}

matrix4& matrix4::operator=(const matrix4& other) {
    if (this != &other) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; ++j) {
                _value[i][j] = other._value[i][j];
            }
        }
    }
    return *this;
}

float* matrix4::operator[](int index) {
    return _value[index];
}

matrix4 matrix4::operator*(const matrix4& other) {
    matrix4 tmp = matrix4();
	for (int i = 0; i < 4; i++)
		for (int y = 0; y < 4; y++)
			for (int x = 0; x < 4; x++)
				tmp._value[i][y] += this->_value[x][y] * other._value[i][x];
	return (tmp);
}

matrix4& matrix4::translate(float x, float y, float z) {
    this->_value[3][0] = x;
	this->_value[3][1] = y;
	this->_value[3][2] = z;
	return (*this);
}

matrix4& matrix4::rotate(float angle, float x, float y, float z) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    float omc = 1.0f - c;
    
    this->_value[0][0] = x * omc + c;
    this->_value[0][1] = y * x * omc + z * s;
    this->_value[0][2] = x * z * omc - y * s;
    this->_value[1][0] = x * y * omc - z * s;
    this->_value[1][1] = y * omc + c;
    this->_value[1][2] = y * z * omc + x * s;
    this->_value[2][0] = x * z * omc + y * s;
    this->_value[2][1] = y * z * omc - x * s;
    this->_value[2][2] = z * omc + c;
    return (*this);
}

matrix4& matrix4::perspective(float fov, float aspect, float near, float far) {
    float rad = fov * M_PI / 180;
	float tanHalfFovy = std::tan(rad / 2.0f);
	
	this->_value[0][0] = 1.0f / (aspect * tanHalfFovy);
	this->_value[1][1] = 1.0f / (tanHalfFovy);
	this->_value[2][2] = -(far + near) / (far - near);
	this->_value[2][3] = -1.0f;
	this->_value[3][2] = -(2.0f * far * near) / (far - near);
	return (*this);
}

float* matrix4::get_value() {
    return &_value[0][0];
}

