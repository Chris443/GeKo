/**
* @class vec3 float
* @author Christian Kati
*
* @brief Basic vector class for mathematical operations
*		  feel free to extend the current version
*	Ideas for improvement:
*	-x,y,z as union/array
*	-reworking lhs and rhs operators
*	-templating -> using no .cpp
*/
#pragma once

#include <algorithm>
#include <math.h>
#include <assert.h>

#include "vec4.h"

namespace gkm {
	class vec3 {
	public:
		vec3(float x = 0, float y = 0, float z = 0);

		vec3(const vec3& other);
		//Move Constructor, evtl. overkill für vector but w/e
		vec3(vec3&& other);

		/*overloaded operators*/
		vec3& operator=(const vec4& other);

		vec3 operator-() { return vec3(-x, -y, -z); }
		vec3& operator=(const vec3& other);

		vec3 operator+(const vec3& other)const;
		vec3 operator-(const vec3& other)const;
		vec3 operator+(const float& scalar)const;
		vec3 operator-(const float& scalar)const;
		vec3 operator*(const float& scalar)const;
		vec3 operator/(const float& scalar)const;

		vec3& operator+=(const vec3& other);
		vec3& operator-=(const vec3& other);
		vec3& operator+=(const float& scalar);
		vec3& operator-=(const float& scalar);
		vec3& operator*=(const float& scalar);
		vec3& operator/=(const float& scalar);

		bool operator==(const vec3& other) const;
		bool operator!=(const vec3& other) const;

		float length() const;

		/*Anmerkung: nicht die richtige länge, aber für z.b. Vergleiche ausreichend.
		sqrt() ist die aufwendigste rechenoperation, die erspart man sich dadurch*/
		float squared_length()const;

		//returns the normalized vector
		vec3 get_normalized() const;
		//normalizes the vector
		void normalize();

		//public to make handling with vectors easier
		float x, y, z;
	private:
	};
	
	vec3 operator+(const float& scalar, const vec3& v);
	vec3 operator-(const float& scalar, const vec3& v);
	vec3 operator*(const float& scalar, const vec3& v);
	vec3 operator/(const float& scalar, const vec3& v);

	float dot(const vec3& v1, const vec3& v2);
	vec3 cross(const vec3& v1, const vec3& v2);
}
