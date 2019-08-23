#include "mat4x4.h"

namespace gkm {

	mat4::mat4()
		:m{
			{1.0, 0.0, 0.0, 0.0}, //first row
			{0.0, 1.0, 0.0, 0.0}, //2nd
			{0.0, 0.0, 1.0, 0.0}, //3
			{0.0, 0.0, 0.0, 1.0}  //4
		}
	{}

	mat4::mat4(float n)
		:m{}
	{
		for (int i = 0; i < 4; ++i) 
			m[i][i] = n;
	}

	mat4::~mat4() {  }

	mat4::mat4(const mat4& other) {
		for (int x = 0; x < 4; ++x) {
			for (int y = 0; y < 4; ++y) {
				m[x][y] = other.m[x][y];
			}
		}
	}

	void mat4::transpose(){
		mat4 other = *this;

		for (int x = 0; x < 4; ++x) {
			for (int y = 0; y < 4; ++y) {
				m[x][y] = other.m[y][x];
			}
		}
	}

	mat4 mat4::operator+(const float& scalar) {
		for (int x = 0; x < 4; ++x) {
			for (int y = 0; y < 4; ++y) {
				m[x][y] += scalar;
			}
		}
		return *this;
	}
	mat4 mat4::operator-(const float& scalar) {
		for (int x = 0; x < 4; ++x) {
			for (int y = 0; y < 4; ++y) {
				m[x][y] -= scalar;
			}
		}
		return *this;
	}
	mat4 mat4::operator*(const float& scalar) {
		for (int x = 0; x < 4; ++x) {
			for (int y = 0; y < 4; ++y) {
				m[x][y] *= scalar;
			}
		}
		return *this;
	}

	mat4 mat4::operator+(const mat4& other) {
		for (int x = 0; x < 4; ++x) {
			for (int y = 0; y < 4; ++y) {
				m[x][y] += other.m[x][y];
			}
		}
		return *this;
	}

	mat4 mat4::operator-(const mat4& other) {
		for (int x = 0; x < 4; ++x) {
			for (int y = 0; y < 4; ++y) {
				m[x][y] -= other.m[x][y];
			}
		}
		return *this;
	}

	//Matrix multiplication is adjusted for column-major multiplication
	mat4 mat4::operator*(const mat4& other) {
		mat4 t(0);
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				for (int k = 0; k < 4; ++k) {
					t.m[i][j] += m[k][i] * other.m[j][k]; 
				}
			}
		}
		return t;
	}

	vec4 mat4::operator*(const vec4& v) {
		float t[4]{0};

		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				t[i] += m[i][j] * v.e[j];
			}
		}
		return vec4(t[0],t[1],t[2],v.e[3]);
	}

 
	/*
	*  1  0  0  0
	*  0  1  0  0
	*  0  0  1  0
	* sx sy sz  1  4th column
	*/
	mat4 mat4::translate(const vec3& v) {
		mat4 mat;
		mat.m[3][0] = v.x;		
		mat.m[3][1] = v.y;
		mat.m[3][2] = v.z;
		return mat;
	}
	// vector values correspond to rotation around given axis
	mat4 mat4::euler_rotate(gkm::vec3 euler_angles) {
		mat4 x_mat;
		mat4 y_mat;
		mat4 z_mat;
		x_mat.m[1][1] = gkm::d_cos(euler_angles.x);
		x_mat.m[1][2] = gkm::d_sin(euler_angles.x);
		x_mat.m[2][1] = -gkm::d_sin(euler_angles.x);
		x_mat.m[2][2] = gkm::d_cos(euler_angles.x);
		
		y_mat.m[0][0] = gkm::d_cos(euler_angles.y);
		y_mat.m[0][2] = -gkm::d_sin(euler_angles.y);
		y_mat.m[2][0] = gkm::d_sin(euler_angles.y);
		y_mat.m[2][2] = gkm::d_cos(euler_angles.y);

		z_mat.m[0][0] = gkm::d_cos(euler_angles.z);
		z_mat.m[0][1] = gkm::d_sin(euler_angles.z);
		z_mat.m[1][0] = -gkm::d_sin(euler_angles.z);
		z_mat.m[1][1] = gkm::d_cos(euler_angles.z);
		//picked this order for no particular reason, rotating with 3 matrices sucks anyways
		return x_mat * y_mat * z_mat;
	}

	mat4 mat4::scale(const vec3& v) {
		mat4 smat; 
		smat.m[0][0] = v.x;
		smat.m[1][1] = v.y;
		smat.m[2][2] = v.z;
		return smat;
	}

	mat4 perspective(float r, float l, float b, float t, float n, float f) {
		mat4 persp;
		persp.m[0][0] = 2*n / (r - l);
		persp.m[1][1] = 2 * n / (t - b);
		persp.m[2][2] = - (f + n) / (f - n);
		persp.m[3][2] = - (2 * f*n) / (f - n);
		persp.m[3][3] = 0;
		persp.m[2][0] = (r + l) / (r - l);
		persp.m[2][1] = (t + b) / (t - b);
		persp.m[2][3] = -1;
		return persp;
	}

	mat4 ortographic(float left, float right, float bottom, float top, float near, float far) {
		mat4 ortho;
		ortho.m[0][0] = 2.0f / (right-left);
		ortho.m[1][1] = 2.0f / (top-bottom);
		ortho.m[2][2] = -2.0f / (far - near);
		ortho.m[3][0] = - (right + left) / (right - left);
		ortho.m[3][1] = -(top + bottom) / (top - bottom);
		ortho.m[3][2] = -(far + near) / (far - near);
		return ortho;
	}

	mat4 lookAt() {
		mat4 m;
		return m;
	}
}