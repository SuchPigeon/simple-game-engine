#include <cmath>

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

float vec3::length() const {
	return std::sqrt(this->x()*this->x() + this->y()*this->y() + this->z()*this->z());
}

float vec3::dot(vec3 v) {
	return this->x()*v.x() + this->y()*v.y() + this->z()*v.z();
}

vec3 vec3::normal() { 
	float l = this->length();
	return vec3(this->x()/l, this->y()/l, this->z()/l);
}
