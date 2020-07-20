#include "Quad.h"

Quad::Quad(float width, float height, const Texture& texture, const glm::vec3& position, const glm::vec3& rotation)
	: Entity(position, rotation, texture), m_Width(width), m_Height(height)
{
	
}

void Quad::onattach()
{
	m_Va.generate();
	GLfloat vertices[] = {
		-0.5f,		   -0.5f,            0.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		-0.5f + m_Width, -0.5,           0.0f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
		-0.5f + m_Width, -0.5f + m_Height, 0.0f,	0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
		-0.5f,         -0.5f + m_Height, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2, 2, 3, 0
	};
	
	m_Vb.Data(vertices, sizeof(vertices), GL_STATIC_DRAW);

	m_Layout.push<float>(3);
	m_Layout.push<float>(3);
	m_Layout.push<float>(2);
	m_Va.addBuffer(m_Vb, m_Layout);
	m_Ib.Data(indices, sizeof(indices), GL_STATIC_DRAW);

	m_Va.unbind();
	m_ModelMatrix = glm::translate(glm::mat4(1.0f), m_Position);
}

void Quad::update()
{
	//m_Texture.bind();
	m_Va.bind();
	m_ModelMatrix = glm::translate(glm::mat4(1.0f), m_Position);
}
