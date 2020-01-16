#include "Model.h"

#include <string>
#include <sstream>

namespace gke {

	Model::Model(const char* filename)
	{
		std::ifstream file;
		try {
			file.open(filename);
		}catch(std::exception &e) {
			std::cout << e.what() << std::endl;
			return;
		}
		std::string line;

		std::vector<gkm::vec3> vertices;
		std::vector<gkm::vec2> uv;
		std::vector<gkm::vec3> normals;
		std::vector<int> vertexIndices, uvIndices, normalIndices;

		while (std::getline(file, line)) {
			std::istringstream iss(line);
			std::string type;
			float v1, v2, v3;
			iss >> type;
			if (type == "v") {
				iss >> v1 >> v2 >> v3;
				vertices.push_back(gkm::vec3(v1, v2, v3));
				continue;
			}
			else if (type == "vt") {
				iss >> v1 >> v2;
				uv.push_back(gkm::vec2(v1, v2));
				continue;
			}
			else if (type == "vn") {
				iss >> v1 >> v2 >> v3;
				normals.push_back(gkm::vec3(v1, v2, v3));
				continue;
			}
			else if (type == "f") {
				int vIdx1[3], vIdx2[3], vIdx3[3];
				int pos = 0;
				std::string vertex1, vertex2, vertex3;
				iss >> vertex1 >> vertex2 >> vertex3;
				std::string token;
				std::stringstream ss(vertex1);
				int c = 0;
				while (std::getline(ss, token, '/')) {
					vIdx1[c] = std::stoi(token);
					c++;
				}
				c = 0;
				ss = std::stringstream(vertex2);
				while (std::getline(ss, token, '/')) {
					vIdx2[c] = std::stoi(token);
					c++;
				}
				c = 0;
				ss = std::stringstream(vertex3);
				while (std::getline(ss, token, '/')) {
					vIdx3[c] = std::stoi(token);
					c++;
				}

				vertexIndices.push_back(vIdx1[0]);
				vertexIndices.push_back(vIdx2[0]);
				vertexIndices.push_back(vIdx3[0]);
				uvIndices.push_back(vIdx1[1]);
				uvIndices.push_back(vIdx2[1]);
				uvIndices.push_back(vIdx3[1]);
				normalIndices.push_back(vIdx1[2]);
				normalIndices.push_back(vIdx2[2]);
				normalIndices.push_back(vIdx3[2]);
			}

			for (int i = 0; i < vertexIndices.size(); ++i) {
				m_vertices.push_back(vertices[vertexIndices[i] - 1]);
				m_uv.push_back(uv[uvIndices[i] - 1]);
				m_normals.push_back(normals[normalIndices[i] - 1]);
			}

		}



	}


	Model::~Model()
	{
	}

}