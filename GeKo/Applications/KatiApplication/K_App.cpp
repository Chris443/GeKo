#include "K_App.h"

K_App::K_App()
	:w(1200, 800, "Example")
{


	init();
}

void K_App::run() {

	float oldTime = glfwGetTime();
	float deltaTime = 0;

	//game loop 
	//TODO: use appropriate timestep
	while (w.isOpen()) {
		//process input (TODO: via input handler)
		gke::processInput(w.get_Handle());
		glfwPollEvents();

		deltaTime = glfwGetTime() - oldTime;
		oldTime = glfwGetTime();
		//update logic()
		update(deltaTime);

		render();
	}
}

void K_App::init() {

	shader.create("./Applications/KatiApplication/Shader/basic.vert",
		"./Applications/KatiApplication/Shader/basic.frag");

	float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	vbo.create(vertices,sizeof(vertices)); 
	ebo.create(indices, sizeof(indices));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void K_App::render() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader.bind();
	gkm::vec3 t(0.0, 0.0, 1.0);
	gkm::mat4 m;
	
	t.x += cos(glfwGetTime());

	shader.setUniform3f("pos", t);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	w.swapBuffers();
}

void K_App::update(float deltaTime) {

}