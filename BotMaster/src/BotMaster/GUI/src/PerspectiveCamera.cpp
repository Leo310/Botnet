#include "BMpch.h"
#include "PerspectiveCamera.h"

namespace GUI
{
	PerspectiveCamera::PerspectiveCamera(float fov, float ratio, float nears, float fars)
		: m_ViewMatrix(glm::mat4(1.0f)), m_ProjectionMatrix(glm::perspective(glm::radians(fov), ratio, nears, fars)), m_Position({0.0f, 0.0f, 0.0f}), m_Rotation({0.0f, 0.0f, 0.0f })
	{
	}

	PerspectiveCamera::~PerspectiveCamera()
	{
	}

	void PerspectiveCamera::update(float deltatime)
	{
		float translationVelocity = CAM_SPEED * deltatime;
		float rotationVelocity = ROTATION_SPEED * deltatime;
		/*
		if (Eventhandler::Keys[GLFW_KEY_UP])
			m_Position.z -= translationVelocity;
		if (Eventhandler::Keys[GLFW_KEY_DOWN])
			m_Position.z += translationVelocity;
		if (Eventhandler::Keys[GLFW_KEY_LEFT])
			m_Position.x -= translationVelocity;
		if (Eventhandler::Keys[GLFW_KEY_RIGHT])
			m_Position.x += translationVelocity;
		if (Eventhandler::Keys[GLFW_KEY_L])
			m_Rotation.y += rotationVelocity;
		if (Eventhandler::Keys[GLFW_KEY_K])
			m_Rotation.y -= rotationVelocity;
		*/
		Recalculate();
	}

	void PerspectiveCamera::Recalculate()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		m_ViewMatrix = glm::inverse(transform);
	}
}
