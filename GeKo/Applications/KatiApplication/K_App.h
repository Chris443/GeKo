#pragma once

#include <iostream>
#include "../../GeKo/window.h"
#include "../../Math/fwd.h"
#include "../../GeKo/Renderer/Buffer.h"
#include "../../GeKo/Renderer/Shader.h"

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
};