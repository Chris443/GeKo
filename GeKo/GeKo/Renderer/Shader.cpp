#include "Shader.h"



Shader::Shader()
{
}


Shader::~Shader()
{
	glDeleteProgram(m_id);
}

void Shader::create(const std::string& vertexShader, const std::string& fragmentShader) {
	int vs = create_shader(GL_VERTEX_SHADER, vertexShader.c_str());
	int fs = create_shader(GL_FRAGMENT_SHADER, fragmentShader.c_str());
	 

	m_id = glCreateProgram();
	glAttachShader(m_id, vs);
	glAttachShader(m_id, fs);
	glLinkProgram(m_id);

	glDeleteShader(vs);
	glDeleteShader(fs);
}

void Shader::checkErrors(int shader, const std::string& shaderType) {
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::"<< shaderType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::bind() {
	glUseProgram(m_id);
}

void Shader::unbind() {
	glUseProgram(0);
}

int Shader::create_shader(GLenum shaderType,const GLchar* source) {
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	switch (shaderType) {
	case GL_VERTEX_SHADER: checkErrors(shader, "VERTEX"); break;
	case GL_FRAGMENT_SHADER: checkErrors(shader, "FRAGMENT"); break;
	default: std::cout << "ERROR::SHADER::UNKOWN_TYPE\n" << std::endl;
	}
	return shader;
}



