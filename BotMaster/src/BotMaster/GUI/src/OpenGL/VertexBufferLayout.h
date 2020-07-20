#pragma once

#include "src/Base.h"

struct Elements
{
	unsigned int type;
	int count;
	bool normalized;

	static unsigned int getTypeSize(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return sizeof(GLfloat);
		case GL_INT: return sizeof(GLint);
		}
	}
};

// (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
class VertexBufferLayout
{
public:
	VertexBufferLayout()
		: m_Stride(0) {};
	~VertexBufferLayout() {};

	inline const std::vector<Elements>& getElements() const { return m_Attribs; };
	inline unsigned int getStride() const { return m_Stride; }

	template<typename T>
	void push(int count)
	{
		static_assert(false);
	}

	template<>
	void push<float>(int count)
	{
		m_Attribs.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * sizeof(GLfloat);
	}

	template<>
	void push<int>(int count)
	{
		m_Attribs.push_back({ GL_INT, count, GL_FALSE });
		m_Stride += count * sizeof(GLint);
	}

private:
	unsigned int m_Stride;
	std::vector<Elements> m_Attribs;
};