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
	cam(gkm::vec3(0.0f, 0.0f, 5.0f), gkm::vec3(0.0f, 0.0f, -1.0f)),
	model("Applications/K_Application/res/barmodel/stall.obj")
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
		glfwPollEvents();
		inputmanager.processInput(w.get_Handle());
		processInput(w.get_Handle(), deltaTime);

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




	w.enable_mouse(true);
	glEnable(GL_DEPTH_TEST);
	scaling = gkm::vec3(1, 1, 1);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	shader.create("./Applications/K_Application/Shader/basic.vert",
		"./Applications/K_Application/Shader/basic.frag");

	vbo.create(&model.m_vertices[0].x, model.m_vertices.size() * sizeof(gkm::vec3));
	uvbuffer.create(&model.m_uv[0].u, model.m_uv.size() * sizeof(gkm::vec2));

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAO);


	gke::Texture texture("./Applications/K_Application/res/barmodel/stallTexture.png");

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
		ImGui::SliderFloat("FoV", &FoV, 0.0f, 360.0f);
		ImGui::Checkbox("Orthographic", &orthographic);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}


	ImGui::Render();
	
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shader.bind();
	//texture.bind();


	gkm::mat4 modelMat;
	
	//column order
	modelMat *= modelMat.translate(gkm::vec3(0.0f, 0.0f, 0.0f) + translation);
	modelMat *= modelMat.euler_rotate(rotation);
	modelMat *= modelMat.scale(scaling);
	
	shader.setMat4("mat", modelMat);
	shader.setMat4("view", cam.getViewMatrix());
	shader.setMat4("proj", projectionMat);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, model.m_vertices.size());
	glBindVertexArray(0);



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


}

void K_App::processInput(GLFWwindow *window,float deltaTime)
{
	if (inputmanager.is_pressed(gke::GKE_KEY::W))
		cam.processMovement(gke::Movement::FORWARD, deltaTime);
	if (inputmanager.is_pressed(gke::GKE_KEY::S))
		cam.processMovement(gke::Movement::BACKWARD, deltaTime);
	if (inputmanager.is_pressed(gke::GKE_KEY::A))
		cam.processMovement(gke::Movement::LEFT, deltaTime);
	if (inputmanager.is_pressed(gke::GKE_KEY::D))
		cam.processMovement(gke::Movement::RIGHT, deltaTime);
	if (inputmanager.is_pressed(gke::GKE_KEY::SPACEBAR))
		cam.processMovement(gke::Movement::UP, deltaTime);
	if (inputmanager.is_pressed(gke::GKE_KEY::L_SHIFT))
		cam.processMovement(gke::Movement::DOWN, deltaTime);
	//look for a better solution(key callback)
	/*if (inputmanager.is_pressed(gke::GKE_KEY::LEFT_CONTROL)) {
		w.enable_mouse(!mouse_active);
		firstcam = !firstcam;
		mouse_active = !mouse_active;
	}*/
	mouseInput(w.get_Handle());
}

void K_App::mouseInput(GLFWwindow *window)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	if (firstcam)
	{
		lastX = xpos;
		lastY = ypos;
		firstcam = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	cam.processMouse(xoffset, yoffset);

}