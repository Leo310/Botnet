#pragma once
#include "Platform - API/OpenGL/Base.h"


#define CAM_SPEED	4.0f
#define ROTATION_SPEED	20.0f	//in degrees

namespace GUI
{
	class PerspectiveCamera
	{
	public:
		PerspectiveCamera(float fov = 45.0f, float ratio = 1920.0f/1080.0f, float near = 0.0f, float far = 100.0f);
		~PerspectiveCamera();

		void update(float deltatime);
	 
	
		void setPosition(const glm::vec3& position) { m_Position = position; Recalculate(); };
		inline glm::vec3 getPosition() const { return m_Position; };

		void setRotation(const glm::vec3& rotation) { m_Rotation = rotation; Recalculate(); };
		inline glm::vec3 getRotation() const { return m_Rotation; };
	
		inline glm::mat4 getProjectionViewMatrix() const { return m_ProjectionMatrix * m_ViewMatrix; };
		inline glm::mat4 getProjectionMatrix() const { return m_ProjectionMatrix; };
		inline glm::mat4 getViewMatrix() const { return m_ViewMatrix; };

	private:
		void Recalculate();
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;

		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
	};
}