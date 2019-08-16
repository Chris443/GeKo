#include "window.h"

namespace gke {

	window::window(int width, int height, const std::string& title)
		:m_width(width), m_height(height), m_title(title)
	{
		init();
	}

	window::~window(){
		glfwTerminate();
	}

	void window::init() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		create_Window();

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}
	}

	void window::create_Window() {
		m_windowHandle = glfwCreateWindow(m_width, m_height, m_title.data(), NULL, NULL);
		if (m_windowHandle == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
		}
		glfwMakeContextCurrent(m_windowHandle);
		glfwSetFramebufferSizeCallback(m_windowHandle, framebuffer_size_callback);
	}

	void window::swapBuffers() {
		glfwSwapBuffers(m_windowHandle);
	}

	bool window::isOpen() {
		return !glfwWindowShouldClose(m_windowHandle);
	}

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void processInput(GLFWwindow *window) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}
}