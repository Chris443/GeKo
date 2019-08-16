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

	//vec4 mat4::operator*(const vec4& v) {

	//}

	vec4 mat4::operator*(const vec4& v) {
		float t[4]{0};

		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				t[i] += m[i][j] * v.e[j];
			}
		}



		return vec4(t[0],t[1],t[2],v.e[3]);
	}
}