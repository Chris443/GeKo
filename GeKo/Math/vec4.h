/**
* @class vec4 float
* @author Christian Kati
*
* @brief Basic vector class for mathematical operations
*		  feel free to extend the current version
*	Ideas for improvement:
*	-x,y,z as union/array
*	-reworking lhs and rhs operators
*	-templating -> no .cpp
*/
#pragma once

#include <algorithm>
#include <exception>
#include <iostream>

#include <math.h>

namespace gkm {

	class vec4 {
	public:
		vec4(float x = 0, float y  = 0, float z = 0, float w = 1);

		vec4(const vec4& other);

		vec4(vec4&& other);

		/*overloaded operators*/
		vec4 operator-() { return vec4(-e[0], -e[1], -e[2], e[3]); }
		vec4& operator=(const vec4& other);
		float& operator[](int idx);

		float e[4];
	private:
	};
}
