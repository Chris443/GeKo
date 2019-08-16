/**
* @class mat4x4 float
* @author Christian Kati
*
* @brief Basic matrix class for mathematical operations
		 uses COLUMN_MAJOR by default
*		  feel free to extend the current version
*	- optimizations like SSE intrinsics, loop blocking/tiling, cache optimization, whatever are neglected
*	-templating
*/

#pragma once
#include <cstring>

#include "vec3.h"

namespace gkm {

	class mat4 {
	public:
		//creates an identitiy matrix
		mat4();
		~mat4();
		//diagonal is set to n
		mat4(float n);

		mat4(const mat4& other);


		void transpose();
		
		mat4 operator+(const float& scalar);
		mat4 operator-(const float& scalar);
		mat4 operator*(const float& scalar);
		mat4 operator+(const mat4& other);
		mat4 operator-(const mat4& other);
		mat4 operator*(const mat4& other);
		vec4 operator*(const vec4& v);


		float m[4][4];
	private:

	};


	mat4 translate(mat4 m, vec3 v);

}