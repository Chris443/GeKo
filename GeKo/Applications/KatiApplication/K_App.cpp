#include "K_App.h"

K_App::K_App()
	:w(1200, 800, "Example")
{
	init();
}

void K_App::run() {

	//game loop 
	//TODO: use appropriate timestep
	while (w.isOpen()) {

		gke::processInput(w.get_Handle());

		//process input (TODO: via input handler)
		glfwPollEvents();

		//update logic

		//render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		w.swapBuffers();
	}
}

void K_App::init() {
	
}