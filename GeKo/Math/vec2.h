#pragma once

#include <algorithm>
#include <math.h>
#include <assert.h>

namespace gkm {
	class vec2 {
	public:
		vec2(float u = 0, float v = 0);

		vec2(const vec2& other);
		//Move Constructor, evtl. overkill für vector but w/e
		vec2(vec2&& other);

		bool operator==(const vec2& other) const;
		bool operator!=(const vec2& other) const;

		//public to make handling with vectors easier
		float u, v;
	private:
	};

}