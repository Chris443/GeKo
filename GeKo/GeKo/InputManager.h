#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <map>

#include "GLFW/glfw3.h"
namespace gke {
	enum GKE_KEY{A = 65,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z}; //GLFW_A = 65

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		bool is_pressed(GKE_KEY key);
		void processInput(GLFWwindow *window);
	private:
		//int keyToGlfw();
		bool KEYS[25];
		std::map<GKE_KEY, bool> keys;

	};

}

#endif