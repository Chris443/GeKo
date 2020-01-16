#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <map>
#include "GLFW/glfw3.h"
namespace gke {
	enum GKE_KEY { SPACEBAR = 32, A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, TAB = 258 , L_SHIFT = 340, LEFT_CONTROL = 341}; //GLFW_A = 65
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		bool is_pressed(GKE_KEY key);
		void processInput(GLFWwindow *window);
	private:
		//int keyToGlfw();
		bool KEYS[29];
		std::map<GKE_KEY, bool> keys;

	};

}

#endif