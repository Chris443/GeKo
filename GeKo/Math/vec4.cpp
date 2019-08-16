#include "vec4.h"

namespace gkm {


	vec4::vec4(float x, float y, float z, float w) :e{x,y,z,w} {}

	vec4::vec4(const vec4& other) : e{ other.e[0] ,other.e[1],other.e[2], other.e[3] } {}

	vec4::vec4(vec4&& other) {
		std::swap(e[0], other.e[0]);
		std::swap(e[1], other.e[1]);
		std::swap(e[2], other.e[2]);
		std::swap(e[3], other.e[3]);
	}

	vec4& vec4::operator=(const vec4& other)
	{
		e[0] = other.e[0];
		e[1] = other.e[1];
		e[2] = other.e[2];
		e[3] = other.e[3];
		return *this;
	}
	//throws at wrong access
	float& vec4::operator[](int idx) {
		try {
			return e[idx];
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

}
 

