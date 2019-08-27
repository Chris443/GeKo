#include "Camera.h"


Camera::Camera(gkm::vec3 position, gkm::vec3 viewDir,gkm::vec3 up)
	:m_position(position), m_viewDirection(viewDir), m_upVector(up)
{

}

Camera::Camera()
	: m_position(gkm::vec3()), m_viewDirection(gkm::vec3()), m_upVector(gkm::vec3(0.0f,1.0f,0.0f))
{
}

Camera::~Camera()
{
}



gkm::mat4 Camera::getViewMatrix() const {
	//return gkm::lookAt(position, m_position + m_viewDirection, m_upVector);
	return gkm::mat4();
}
