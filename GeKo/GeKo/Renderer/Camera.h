#pragma once

#include "../../Math/fwd.h"

class Camera
{
public:
	Camera(gkm::vec3 position, gkm::vec3 viewDir, gkm::vec3 up);
	Camera();
	~Camera();

	gkm::mat4 getViewMatrix() const;
private:
	gkm::vec3 m_position;
	gkm::vec3 m_viewDirection;
	gkm::vec3 m_upVector;

	gkm::mat4 m_viewMatrix;
};

