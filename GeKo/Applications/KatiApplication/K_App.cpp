#include "K_App.h"

K_App::K_App()
	:w(1200, 800, "Example")
{
	init();
}

void K_App::run() {

	float oldTime = static_cast<float>(glfwGetTime());
	float deltaTime = 0;

	//game loop 
	//TODO: use appropriate timestep
	while (w.isOpen()) {
		//process input (TODO: via input handler)
		gke::processInput(w.get_Handle());
		glfwPollEvents();

		deltaTime = static_cast<float>(glfwGetTime()) - oldTime;
		oldTime = static_cast<float>(glfwGetTime());
		//update logic()
		update(deltaTime);

		render();
	}
}

void K_App::init() {
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	shader.create("./Applications/KatiApplication/Shader/basic.vert",
		"./Applications/KatiApplication/Shader/basic.frag");

	float vertices[] = {
	//positions			//colors
	 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,// top right
	 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,// bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,// bottom left
	-0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,// top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 2,     // second triangle
		3, 0, 2   // first triangle
	};
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	vbo.create(vertices, sizeof(vertices));
	ebo.create(indices, sizeof(indices));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float) ));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}

void K_App::render() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader.bind();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	w.swapBuffers();
}

void K_App::update(float deltaTime) {
	gkm::vec3 t(0.0, 0.0, 1.0);
	gkm::mat4 m;
	float v = static_cast<float>(glfwGetTime() * 30);

	t.x = gkm::d_cos(v);

	gkm::mat4 transformMat;

	//transformMat.translate(gkm::vec3(gkm::d_cos(v),0,0));	
	transformMat.euler_rotate( gkm::vec3(0,v,v) );
	//transformMat.euler_rotate(gkm::vec3(0, v, 0));
	


	shader.setMat4("mat", transformMat);
}