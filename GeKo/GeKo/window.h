#pragma once

/**
* @class window class
* @author Christian Kati
*
* @brief window wrapper for GLFW Windows
* @TODO move window & rework for system based (windows,linux,apple) use
*
*/

#include <string>
#include <iostream>

#include <glad/glad.h>
#include "GLFW/glfw3.h"

namespace gke {
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow *window);

	class window
	{
	public:
		window(int width, int height, const std::string& title);
		~window();

		void create_Window();
		void swapBuffers();
		bool isOpen();

		GLFWwindow* get_Handle() { return m_windowHandle; }

	private:
		void init();
		GLFWwindow* m_windowHandle;

		int m_height, m_width;
		std::string m_title;
	};
}

