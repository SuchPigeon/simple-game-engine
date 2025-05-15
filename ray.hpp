#ifndef RAY_HPP
#define RAY_HPP

#include "vec3.hpp"

struct ray {
	point3 p;
	vec3 v;
	float t;
};

#endif
