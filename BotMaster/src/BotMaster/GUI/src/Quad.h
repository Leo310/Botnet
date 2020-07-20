#pragma once

#include "src/Base.h"
#include "Entity.h"

class Quad : public Entity
{
public:
	Quad()
		: m_Width(0), m_Height(0) {}
	Quad(float width, float height, const Texture& texture, const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& rotation = glm::vec3(0.0f, 0.0f, 0.0f));
		
	void onattach();

	void update() override;
	void setWidth(float width) { m_Width = width; };
	inline float getWidth() const { return m_Width; };

	inline float getHeight() const { return m_Height; };
	void setHeight(float height) { m_Height = height; };
private:
	float m_Width;
	float m_Height;
};