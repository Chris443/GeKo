#include "InputManager.h"

namespace gke {

	InputManager::InputManager()
	{
		keys[A] = false;
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::processInput(GLFWwindow *window) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
		for (int i = 65; i < 91; ++i) {
			keys[(GKE_KEY)i] = glfwGetKey(window, i);
		}
		keys[(GKE_KEY)32] = glfwGetKey(window, 32);
		keys[(GKE_KEY)258] = glfwGetKey(window, 258);
		keys[(GKE_KEY)340] = glfwGetKey(window, 340);
		keys[(GKE_KEY)341] = glfwGetKey(window, 341);
	}

	bool InputManager::is_pressed(GKE_KEY key) {
		return keys[key];
	}
}
/*
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		inputmanager.
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}*/