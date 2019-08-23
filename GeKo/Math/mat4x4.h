/**
* @class mat4x4 float
* @author Christian Kati
*
* @brief Basic matrix class for mathematical operations
		 Operations use Column Major by default
*
*	- optimizations like SSE intrinsics, loop blocking/tiling, cache optimization, whatever are neglected
* @TODO:
*   -templating
*	-combining rotation matrices/using one + arbitrary axis
*	-implement quaternions
*/

#pragma once
#include <cstring>

#include "fwd.h"

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
		mat4 translate(const vec3& v);
		mat4 euler_rotate(gkm::vec3 euler_angles);
		mat4 scale(const vec3& v);

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
}