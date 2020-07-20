#pragma once

#include "Base.h"
#include "OpenGL/Texture.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/VertexBufferLayout.h"
#include "OpenGL/VertexArray.h"


class Entity
{
public:

	virtual ~Entity() {};

	virtual void update() = 0;

	virtual void setTexture(const Texture& texture) { m_Texture = texture; }
	virtual inline Texture& getTexture() { return m_Texture; }

	virtual void setPosition(const glm::vec3& position) { m_Position = position; };
	virtual inline const glm::vec3& getPosition() const { return m_Position; };

	virtual void setRotation(const glm::vec3& rotation) { m_Rotation = rotation; };
	virtual inline const glm::vec3& getRotation() const { return m_Rotation; };

	virtual inline const glm::mat4& getModelMatrix() const { return m_ModelMatrix; };

	virtual inline const VertexBufferLayout& getDataLayout() const { return m_Layout; };
	virtual inline const VertexBuffer& getVertexBuffer() { return m_Vb; };
	virtual inline const IndexBuffer& getIndexBuffer() const { return m_Ib; };

protected:
	Entity()
		: m_Position({ 0,0,0 }), m_Rotation({ 0,0,0 }), m_ModelMatrix(1.0f), m_Texture() {}
	Entity(const glm::vec3& position, const glm::vec3& rotation, const Texture& texture)
		: m_Position(position), m_Rotation(rotation), m_ModelMatrix(1.0f), m_Texture(texture) {};

	glm::vec3 m_Position;
	glm::vec3 m_Rotation;

	glm::mat4 m_ModelMatrix;

	Texture m_Texture;

	VertexBuffer m_Vb;
	IndexBuffer m_Ib;
	VertexBufferLayout m_Layout;
	VertexArray m_Va;
};