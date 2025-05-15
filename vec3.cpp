#include "vec3.hpp"

vec3::vec3() {};

vec3::vec3(float x, float y, float z) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

float vec3::x() const { return v[0]; }
float vec3::y() const { return v[1]; }
float vec3::z() const { return v[2]; }

void vec3::setx(const float _x) { v[0] = _x; }
void vec3::sety(const float _y) { v[1] = _y; }
void vec3::setz(const float _z) { v[2] = _z; }

