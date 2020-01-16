#include "vec2.h"

namespace gkm {

	vec2::vec2(float u, float v)
		:u(u), v(v) {}

	vec2::vec2(const vec2& other)
		:u(other.u), v(other.v){}

	vec2::vec2(vec2&& other) {
		std::swap(u, other.u);
		std::swap(v, other.v);
	}

	bool vec2::operator==(const vec2& other) const {
		if (u == other.u && v == other.v)
			return true;
		return false;
	}
	bool vec2::operator!=(const vec2& other) const {
		return !(*this == other);
	}

}