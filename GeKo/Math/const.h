#pragma once

#include <math.h>

const float PI = 3.14159f;
const float EPSILON = 0.000001f;

namespace gkm {
	inline float degree_to_radians(float degree) {
		return degree * (PI / 180.0f);
	}
	inline float radians_to_degree(float radians) {
		return radians * (180.0f / PI);
	}
	//expects angle in degree
	inline float d_cos(float angle){
		float t = static_cast<float>(cos(degree_to_radians(angle)));
		return (t < EPSILON && t > -EPSILON) ? 0 : t;
	}
	//expects angle in degree
	inline float d_sin(float angle){
		float t = static_cast<float>(sin(degree_to_radians(angle)));
		return (t < EPSILON && t > -EPSILON) ? 0 : t;
	}
}
