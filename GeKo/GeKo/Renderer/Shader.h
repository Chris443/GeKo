#pragma once

#include <string>
#include <iostream>

#include "glad/glad.h"

class Shader
{
public:
	Shader();
	~Shader();

	void create(const std::string& vertexShader, const std::string& fragmentShader);

	void bind();
	void unbind();
private:
	int create_shader(GLenum shaderType, const GLchar* source);
	void checkErrors(int shader,const std::string& shaderType);

	int m_id;
	int m_vertexShader;
	int m_fragmentShader;
};

