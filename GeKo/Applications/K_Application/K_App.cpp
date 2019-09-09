#include "K_App.h"
#include "Data.h"
#include "../../GeKo/Renderer/stb_image.h"

#include "../../ImGui/imgui.h"
#include "../../ImGui/imgui_impl_glfw.h"
#include "../../ImGui/imgui_impl_opengl3.h"

#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"

K_App::K_App()
	:w(scr_width, scr_height, "Example"), orthographic(false), FoV(90.0f),
	cam(gkm::vec3(0.0f,0.0f,5.0f), gkm::vec3(0.0f,0.0f,0.0f))
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
		//gke::processInput(&w);
		glfwPollEvents();
		inputmanager.processInput(w.get_Handle());
		
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

void K_App::init(){
	glEnable(GL_DEPTH_TEST);
	scaling = gkm::vec3(0.5, 0.5, 0.5);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	shader.create("./Applications/K_Application/Shader/basic.vert",
		"./Applications/K_Application/Shader/basic.frag");

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	vbo.create(vertices, sizeof(vertices));
	ebo.create(&indices[0], indices.size() * sizeof(float) );

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float) ));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	gke::Texture texture("./Applications/K_Application/res/Textures/wall.jpg");
}

void K_App::render() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	{
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		ImGui::Begin("Gui!");                     
		ImGui::SliderFloat3("Translation", &translation.x, -10.0f, 10.0f);   
		ImGui::SliderFloat3("Rotation", &rotation.x, 0.0f, 360.0f);
		ImGui::SliderFloat3("Scaling", &scaling.x, -1.0f, 10.0f);
		ImGui::SliderFloat("FoV", &FoV,0.0f, 360.0f);
		ImGui::Checkbox("Orthographic" , &orthographic);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}


	ImGui::Render();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shader.bind();
	//texture.bind()
	glBindVertexArray(VAO);

	gkm::vec3 cubePositions[] = {
		gkm::vec3(0.0f,0.0f,0.0f),
		gkm::vec3(2.0f,0.0f,-15.0f),
		gkm::vec3(-1.5f,0.0f,-2.0f)
	};


	//update objects
	for (int i = 0; i < 3; ++i) {

		gkm::mat4 modelMat;

		//column order
		modelMat *= modelMat.translate(cubePositions[i] + translation);
		modelMat *= modelMat.euler_rotate(rotation);
		modelMat *= modelMat.scale(scaling);

		shader.setMat4("mat", modelMat);
		shader.setMat4("view", cam.getViewMatrix());
		shader.setMat4("proj", projectionMat);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}


	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	w.swapBuffers();
}

void K_App::update(float deltaTime) {
	/*************proj mat**************/
	float aspectRatio = scr_width / scr_height;
	projectionMat = gkm::perspective(gkm::degree_to_radians(FoV), aspectRatio, 0.1f, 100.0f);

	if (orthographic) {
		float aspectRatio = scr_width / scr_height;
		projectionMat = gkm::ortographic(-aspectRatio, aspectRatio, -aspectRatio, aspectRatio, 0.1f, 100.0f);
	}
	/**********************************/

	float velocity = 0.05f;
	if (inputmanager.is_pressed(gke::GKE_KEY::W))
		cam.processMovement(gke::Movement::FORWARD, deltaTime);
	if (inputmanager.is_pressed(gke::GKE_KEY::S))
		cam.processMovement(gke::Movement::BACKWARD, deltaTime);
	if (inputmanager.is_pressed(gke::GKE_KEY::A))
		cam.processMovement(gke::Movement::LEFT, deltaTime);
	if (inputmanager.is_pressed(gke::GKE_KEY::D))
		cam.processMovement(gke::Movement::RIGHT, deltaTime);
		//	cam.setPosition();


		//	cam.updateCamera();

	cam.updateCamera();



}