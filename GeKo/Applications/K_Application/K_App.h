#pragma once

#include <iostream>
#include "../../glm/gtx/euler_angles.hpp"
#include "../../GeKo/window.h"
#include "../../GeKo/InputManager.h"
#include "../../Math/fwd.h"
#include "../../GeKo/Renderer/Buffer.h"
#include "../../GeKo/Renderer/Shader.h"
#include "../../GeKo/Renderer/Texture.h"
#include "../../GeKo/Renderer/Camera.h"

const float scr_width = 800.0f;
const float scr_height = 600.0f;

class K_App {
public:
	K_App();
	void run();
	void processInput(GLFWwindow *window);
	void mouseInput(GLFWwindow *window);
private:
	void init();
	void render();
	void update(float deltaTime);

	gke::window w;
	gke::InputManager inputmanager;
	gke::VertexBuffer vbo;
	gke::IndexBuffer ebo;
	unsigned int VAO;
	gke::Shader shader;
	gke::Camera cam;

	gkm::vec3 translation;
	gkm::vec3 rotation;
	gkm::vec3 scaling;
	float FoV;

	bool orthographic;


	gkm::mat4 viewMat;
	gkm::mat4 projectionMat;

	gkm::vec3 cameraPos = gkm::vec3(0.0f, 0.0f, 3.0f);
	gkm::vec3 cameraFront = gkm::vec3(0.0f, 0.0f, -1.0f);
	gkm::vec3 cameraUp = gkm::vec3(0.0f, 1.0f, 0.0f);
};