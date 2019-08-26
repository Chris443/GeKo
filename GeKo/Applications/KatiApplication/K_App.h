#pragma once

#include <iostream>
#include "../../glm/gtx/euler_angles.hpp"
#include "../../GeKo/window.h"
#include "../../Math/fwd.h"
#include "../../GeKo/Renderer/Buffer.h"
#include "../../GeKo/Renderer/Shader.h"
#include "../../GeKo/Renderer/Texture.h"

const float scr_width = 800.0f;
const float scr_height = 600.0f;

class K_App {
public:
	K_App();
	void run();
private:
	void init();
	void render();
	void update(float deltaTime);

	gke::window w;
	gke::VertexBuffer vbo;
	gke::IndexBuffer ebo;
	unsigned int VAO;
	gke::Shader shader;

	gkm::vec3 translation;
	gkm::vec3 rotation;
	gkm::vec3 scaling;
	float FoV;

	bool orthographic;

};