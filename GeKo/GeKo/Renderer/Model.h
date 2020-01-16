#pragma once

#include <vector>
#include <fstream>

#include "../../Math/fwd.h"

namespace gke {

	class Model
	{
	public:
		Model(const char* filename);
		~Model();
		std::vector<gkm::vec3> m_vertices;
		std::vector<gkm::vec2> m_uv;
		std::vector<gkm::vec3> m_normals;
	};

}

