#pragma once

/*
* Under Construction
*/

#include "../../ImGui/imgui.h"
#include "../../ImGui/imgui_impl_glfw.h"
#include "../../ImGui/imgui_impl_opengl3.h"

namespace gke {

	class Gui
	{
	public:
		Gui(GLFWwindow* window);
		~Gui();
		void newFrame();
	private:
	};

}