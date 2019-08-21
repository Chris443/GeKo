#pragma once

#include <string>
#include <ostream>
#include <fstream>
#include <streambuf>
#include <iostream>

#include "glad/glad.h"

#include "../../Math/vec3.h"
#include "../../Math/mat4x4.h"

namespace gke {

	class Shader
	{
	public:
		Shader();
		~Shader();

		void create(const std::string& vertexShader, const std::string& fragmentShader);

		void bind();
		void unbind();

		void setVec3(const std::string& name, gkm::vec3 v);
		void setMat4(const std::string& name, gkm::mat4 m);
	private:
		int create_shader(GLenum shaderType, const GLchar* source);
		void checkErrors(int shader, const std::string& shaderType);

		int m_id;
		int m_vertexShader;
		int m_fragmentShader;
	};

}