#include "vec3.h"

namespace gkm {

	vec3::vec3(float x, float y, float z)
		: x(x), y(y), z(z) {}

	vec3::vec3(const vec3& other)
		: x(other.x), y(other.y), z(other.z) {}


	vec3::vec3(vec3&& other) {
		std::swap(x, other.x);
		std::swap(y, other.y);
		std::swap(z, other.z);
	}

	vec3& vec3::operator=(const vec4& other) {
		x = other.e[0] / other.e[3];
		y = other.e[1] / other.e[3];
		z = other.e[2] / other.e[3];
		return *this;
	}

	vec3& vec3::operator=(const vec3& other) {
		if (this != &other) { // C++ Guidelines: perform no action on self-assignment
			x = other.x;
			y = other.y;
			z = other.z;
		}
		return *this;
	}

	vec3 vec3::operator+(const vec3& other) const{
		return vec3(x + other.x, y + other.y, z + other.z);
	}
	vec3 vec3::operator-(const vec3& other) const{
		return vec3(x - other.x, y - other.y, z - other.z);
	}

	vec3 vec3::operator+(const float& scalar) const {
		return vec3(x+scalar,y+scalar,z+scalar);
	}
	vec3 vec3::operator-(const float& scalar) const {
		return vec3(x - scalar, y - scalar, z - scalar);
	}
	vec3 vec3::operator*(const float& scalar) const {
		return vec3(x * scalar, y * scalar, z * scalar);
	}
	vec3 vec3::operator/(const float& scalar) const {
		return vec3(x / scalar, y / scalar, z / scalar);
	}

	/****
	* Note: Rückgabe als void auch möglich
	*		aber: v1 += v2 += v3 würde nicht funktionieren (chaining), da (v.r.n.l.) v2+=v3 void zurückgeben würde (v2 würde aber korrekt verändert werden)
	*		--> Auf Semantik achten, d.h. +,-,*,/ als value, +=,-=,.... als referenz zurück geben
	*****/
	vec3& vec3::operator+=(const vec3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	vec3& vec3::operator-=(const vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	vec3& vec3::operator+=(const float& scalar) {
		x += scalar;
		y += scalar;
		z += scalar;
		return *this;
	}

	vec3& vec3::operator-=(const float& scalar) {
		x -= scalar;
		y -= scalar;
		z -= scalar;
		return *this;
	}


	vec3& vec3::operator*=(const float& scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;

	}
	vec3& vec3::operator/=(const float& scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}


	/*********/



	bool vec3::operator==(const vec3& other) const {
		if (x == other.x && y == other.y && z == other.z)
			return true;
		return false;
	}

	bool vec3::operator!=(const vec3& other) const{
		return !(*this == other);
	}

	float vec3::length() const {
		return static_cast<float>(sqrt(x*x + y * y + z * z));
	}

	float vec3::squared_length() const {
		return x * x + y * y + z * z;
	}

	vec3 vec3::get_normalized() const{
		return vec3(x / length(), y / length(), z / length());
	}

	void vec3::normalize() {
		float l = length();
		x /= l;
		y /= l; 
		z /= l;
	}

	float dot(const vec3& v1, const vec3& v2){
		return v1.x*v2.x + v1.y * v2.y + v1.z*v2.z;
	}

	vec3 cross(const vec3& v1, const vec3& v2) {
		return vec3(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x *v2.z,
			v1.x * v2.y - v1.y *v2.x);
	}

	vec3 operator+(const float& scalar,const vec3& v) {
		return vec3(v.x + scalar, v.y + scalar, v.z + scalar);
	}
	vec3 operator-(const float& scalar, const vec3& v) {
		return vec3(v.x - scalar, v.y - scalar, v.z - scalar);
	}
	vec3 operator*(const float& scalar, const vec3& v) {
		return vec3(v.x * scalar, v.y * scalar, v.z * scalar);
	}
	vec3 operator/(const float& scalar, const vec3& v) {
		return vec3(v.x / scalar, v.y / scalar, v.z / scalar);
	}
}