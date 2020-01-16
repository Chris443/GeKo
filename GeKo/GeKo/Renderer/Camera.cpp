#include "Camera.h"

namespace gke {

	Camera::Camera(gkm::vec3 position, gkm::vec3 lookAt, gkm::vec3 up)
		:m_position(position), m_lookAt(lookAt), m_up(up), yaw(YAW), pitch(PITCH)
	{
	}

	Camera::~Camera()
	{
	}

	gkm::mat4 Camera::getViewMatrix() const {
		return gkm::lookAt(m_position, m_position + m_lookAt, m_up);
	}

	void Camera::processMovement(Movement movement, float deltaTime) {
		float velocity = 5.0f * deltaTime;
		if (movement == FORWARD)
			m_position += m_lookAt * velocity;
		if (movement == BACKWARD)
			m_position -= m_lookAt * velocity;
		if (movement == LEFT)
			m_position -= gkm::cross(m_lookAt, m_up).get_normalized() * velocity;
		if (movement == RIGHT)
			m_position += gkm::cross(m_lookAt, m_up).get_normalized() * velocity;
		if (movement == UP)
			m_position += m_up * velocity;
		if (movement == DOWN)
			m_position -= m_up * velocity;
	}

	void Camera::processMouse(float xoffset, float yoffset) {
		float sensitivity = 0.05f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		m_lookAt.x = gkm::d_cos(pitch) * gkm::d_cos(yaw);
		m_lookAt.y = gkm::d_sin(pitch);
		m_lookAt.z = gkm::d_cos(pitch)  * gkm::d_sin(yaw);
		m_lookAt.normalize();
	}
}