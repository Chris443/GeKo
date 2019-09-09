#include "Camera.h"

namespace gke {

	Camera::Camera(gkm::vec3 position, gkm::vec3 lookAt, gkm::vec3 up)
		:m_position(position), m_lookAt(lookAt), m_up(up)
	{
		init();
	}

	Camera::~Camera()
	{
	}

	void Camera::init() {
		m_forward = m_position - m_lookAt;
		m_forward.normalize();
		//m_up = gkm::vec3(0.0f,1.0f,0.0f);
		m_right = gkm::cross(m_up,m_forward);
	}
	//careful: reference-up vector is 0,1,0
	void Camera::updateCamera(){
		m_forward = m_position - m_lookAt;
		m_forward.normalize();
		m_right = gkm::cross(gkm::vec3(0.0f,1.0f,0.0f), m_forward);
		m_right.normalize();
		m_up = gkm::cross(m_forward , m_right);
	}

	gkm::mat4 Camera::getViewMatrix() const {
		return gkm::lookAt(m_position, m_lookAt, m_up);
	}

	void Camera::processMovement(Movement movement, float deltaTime) {
		float velocity = 5.0f * deltaTime;
		if (movement == FORWARD)
			m_position -= m_forward * velocity;
		if (movement == BACKWARD)
			m_position += m_forward * velocity;
		if (movement == LEFT)
			m_position += m_right * velocity;
		if (movement == RIGHT)
			m_position -= m_right * velocity;
		updateCamera();
	}
}