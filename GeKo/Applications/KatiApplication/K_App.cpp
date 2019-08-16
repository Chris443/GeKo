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

		//process input (TODO: via input handler)
		gke::processInput(w.get_Handle());
		glfwPollEvents();


		//update logic
		step();


		//render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		w.swapBuffers();
	}
}

void K_App::init() {

}

void K_App::step() {
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};
	
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

 
}