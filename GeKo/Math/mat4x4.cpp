#include "mat4x4.h"

namespace gkm {

	mat4::mat4()
		:m{
			{1.0, 0.0, 0.0, 0.0}, //first column
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

	mat4 mat4::operator*(const mat4& other) {
		mat4 t(0);
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				for (int k = 0; k < 4; ++k) {
					t.m[i][j] += m[i][k] * other.m[k][j];
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
	void mat4::translate(const vec3& v) {
		m[3][0] = v.x;		
		m[3][1] = v.y;
		m[3][2] = v.z;
	}

	void mat4::euler_rotate(gkm::vec3 euler_angles) {
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
		//picked this order for no particular reason, rotating with 3 matrices sucks an
		*this = x_mat * y_mat * z_mat * (*this) ;
	}

	void mat4::scale(const vec3& v) {
		m[0][0] = v.x;
		m[1][1] = v.y;
		m[2][2] = v.z;
	}
}