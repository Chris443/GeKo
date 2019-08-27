/**
* @class mat4x4 float
* @author Christian Kati
*
* @brief Basic matrix class for mathematical operations
		 Column Major Layout:
		0 4  8 12
		1 5  9 13
		2 6 10 14
		3 7 11 15
		Matrix is sequential in memory:
		0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
		--> all operations are adjusted for column major matrices
		0 4 8 12 1 5 9 13 2 6 10 14 3 7 11 15

		[column][row] (reversed, to pick correct value)
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
		mat4(float* other);

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

		mat4& operator*=(const mat4& other);


		float m[4][4];
	private:

	};
	mat4 perspective(float fov, float aspectRatio, float near, float far);
	mat4 ortographic(float left, float right, float bottom, float top, float near, float far);

	mat4 lookAt(const gkm::vec3& eye, const gkm::vec3& center, const gkm::vec3& up = gkm::vec3(0.0f,1.0f,0.0f) );
}