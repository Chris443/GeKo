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
		:m{
			{ n, 0.0, 0.0, 0.0 }, //first column
			{ 0.0, n, 0.0, 0.0 }, //2nd
			{ 0.0, 0.0, n, 0.0 }, //3
			{ 0.0, 0.0, 0.0, n }  //4
	}{}


	mat4::~mat4() {  }

	mat4::mat4(const mat4& other) {
		for (int x = 0; x < 4; ++x) {
			for (int y = 0; y < 4; ++y) {
				m[x][y] = other.m[x][y];
			}
		}
	}

	mat4::mat4(float* other) {
		if (!other) {
			std::cout << "Matrix Copy Failed" << std::endl;
			return;
		}
		for (int x = 0; x < 4; ++x) {
			for (int y = 0; y < 4; ++y) {
				m[x][y] = *other++;
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
		mat4 t(0.0f);
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				for (int k = 0; k < 4; ++k) {
					t.m[j][i] += m[k][i] * other.m[j][k];
				}
			}
		}
		return t;
	}
	mat4& mat4::operator*=(const mat4& other) {
		return *this = *this * other;

	}

	vec4 mat4::operator*(const vec4& v) {
		float t[4]{ 0 };

		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				t[i] += m[j][i] * v.e[j];
			}
		}

		if (t[3] != 0.0f) {
			t[0] /= t[3]; t[1] /= t[3]; t[2] /= t[3];
		}


		return vec4(t[0],t[1],t[2],v.e[3]);
	}

 
	/*
	*  1  0  0  0
	*  0  1  0  0
	*  0  0  1  0
	* sx sy sz  1  4th column
	*/
	//Translate works
	mat4 mat4::translate(const vec3& v) {
		mat4 mat;
		mat.m[3][0] = v.x;		
		mat.m[3][1] = v.y;
		mat.m[3][2] = v.z;
		return mat;
	}
	/*
	* Rotates around Given Axis in Degrees in order  X * Y * Z
	* Expects Degrees! 
	*/
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
		//picked this order for no particular reason
		// X*Y*Z, da column Major. vergleiche glm::eulerAnglesXYZ(x,y,z)  
		// !!glm expects radians, while here degrees are expects(d_sin/d_cos)
		return x_mat * y_mat * z_mat;
	}
	//Scaling works
	mat4 mat4::scale(const vec3& v) {
		mat4 mat;
		mat.m[0][0] = v.x;
		mat.m[1][1] = v.y;
		mat.m[2][2] = v.z;
		return mat;
	}
	//should work
	mat4 perspective(float fov, float aspectRatio, float near, float far) {
		mat4 persp;
		persp.m[0][0] = 1 / tan(fov / 2);
		persp.m[1][1] = aspectRatio / tan(fov / 2); //aspectRatio is width/height
		persp.m[2][2] = (near + far) / (near - far);
		persp.m[3][2] = 2 * near * far / (near - far);
		persp.m[3][3] = 0;
		persp.m[2][3] = -1;

		return persp;
	}

	//needs testing
	mat4 ortographic(float left, float right, float bottom, float top, float near, float far) {
		mat4 ortho;
		ortho.m[0][0] = 2.0f / (right-left);
		ortho.m[1][1] = 2.0f / (top-bottom);
		ortho.m[2][2] = -2.0f / (far - near);
		ortho.m[3][0] = -(right + left) / (right - left);
		ortho.m[3][1] = -(top + bottom) / (top - bottom);;
		ortho.m[3][2] = -(far + near) / (far - near);;

		ortho.m[3][3] = 1;
		return ortho;
	}

	mat4 lookAt(const gkm::vec3& pos, const gkm::vec3& look, const gkm::vec3& up) {
		gkm::mat4 viewRot,viewTrans;

		gkm::vec3 forward(pos - look);
		forward.normalize();
		gkm::vec3 right(gkm::cross(up, forward));
		right.normalize();
		gkm::vec3 up_vec(gkm::cross(forward, right));
	//	up_vec.normalize();

		viewRot.m[0][0] = right.x;
		viewRot.m[0][1] = up_vec.x;
		viewRot.m[0][2] = forward.x;
		
		viewRot.m[1][0] = right.y;
		viewRot.m[1][1] = up_vec.y;
		viewRot.m[1][2] = forward.y;
		
		viewRot.m[2][0] = right.z;
		viewRot.m[2][1] = up_vec.z;
		viewRot.m[2][2] = forward.z;

		viewTrans.m[3][0] = -pos.x;
		viewTrans.m[3][1] = -pos.y;
		viewTrans.m[3][2] = -pos.z;


		return viewRot * viewTrans;
	}
}