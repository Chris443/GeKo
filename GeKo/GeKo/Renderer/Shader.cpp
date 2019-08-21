#include "Shader.h"

namespace gke {

	Shader::Shader()
	{
	}


	Shader::~Shader()
	{
		glDeleteProgram(m_id);
	}

	void Shader::create(const std::string& vertexSource, const std::string& fragmentSource) {

		std::ifstream t(vertexSource);
		std::string vertexShader((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());
		t = std::ifstream(fragmentSource);
		std::string fragmentShader((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());



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
			std::cout << "ERROR::SHADER::" << shaderType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}

	void Shader::bind() {
		glUseProgram(m_id);
	}

	void Shader::unbind() {
		glUseProgram(0);
	}

	int Shader::create_shader(GLenum shaderType, const GLchar* source) {
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

	void Shader::setVec3(const std::string& name, gkm::vec3 v) {
		glUniform3f(glGetUniformLocation(m_id, name.c_str()), v.x, v.y, v.z);
	}


	void Shader::setMat4(const std::string& name, gkm::mat4 m) {
		glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &m.m[0][0]);
	}


}