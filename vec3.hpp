#ifndef VEC_3_HPP
#define VEC_3_HPP

class vec3 {
public:
	vec3();
	vec3(float,float,float); 
	float x() const;
	float y() const;
	float z() const;
	void setx(const float);
	void sety(const float);
	void setz(const float);
	float length() const;
	vec3 normal();
	float dot(vec3);
	inline vec3 operator-() const {
		return vec3(this->x(), this->y(), this->z());
	}
	inline float& operator[](int ind) {
		return v[ind];
	}
private:
	float v[3];
};

inline vec3 operator*(float t, vec3 v) {
	return vec3(t*v.x(), t*v.y(), t*v.z());
}

inline vec3 operator+(vec3 lv, vec3 rv) {
	return vec3(lv[0] + rv[0], lv[1] + rv[1], lv[2] + rv[2]);
}

inline vec3 operator-(vec3 lv, vec3 rv) {
	return vec3(lv[0] - rv[0], lv[1] - rv[1], lv[2] - rv[2]);
}

using point3 = vec3;
using color3 = vec3;

#endif
