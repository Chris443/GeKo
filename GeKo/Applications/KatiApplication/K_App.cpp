#include "K_App.h"

#include "../../ImGui/imgui.h"
#include "../../ImGui/imgui_impl_glfw.h"
#include "../../ImGui/imgui_impl_opengl3.h"

K_App::K_App()
	:w(1200, 800, "Example")
{
	init();
}

void K_App::run() {

	float oldTime = static_cast<float>(glfwGetTime());
	float deltaTime = 0;

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(w.get_Handle(), true);
	ImGui_ImplOpenGL3_Init("#version 460");
	ImGui::StyleColorsDark();

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

		//int display_w, display_h;
		//glfwGetFramebufferSize(w.get_Handle(), &display_w, &display_h);
		//glViewport(0, 0, display_w, display_h);
		render();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
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
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	{
		static float f = 0.0f;
		static int counter = 0;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	ImGui::Render();


	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	shader.bind();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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