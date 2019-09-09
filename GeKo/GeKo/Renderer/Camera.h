#pragma once

#include "../../Math/fwd.h"

namespace gke {
	enum Movement {
		FORWARD,
		BACKWARD,
		RIGHT,
		LEFT
	};


	class Camera
	{
	public:
		Camera(gkm::vec3 position, gkm::vec3 lookAt, gkm::vec3 up = gkm::vec3(0.0f,1.0f,0.0f));
		~Camera();

		void setPosition(gkm::vec3 pos) { m_position = pos; };
		void setLookAt(gkm::vec3 look) { m_lookAt = look; };
		void setUp(gkm::vec3 up) { m_up = up; };

		void processMovement(Movement movement, float deltaTime);

		void updateCamera();

		gkm::mat4 getViewMatrix() const;
	private:
		gkm::vec3 m_position;
		gkm::vec3 m_lookAt;

		gkm::vec3 m_forward;
		gkm::vec3 m_up;
		gkm::vec3 m_right;

		gkm::mat4 m_viewMatrix;

		void init();
	};
}