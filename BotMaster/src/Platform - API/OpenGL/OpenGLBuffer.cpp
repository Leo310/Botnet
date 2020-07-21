#include "BMpch.h"

#include "OpenGLBuffer.h"

#include "OpenGLBase.h"

namespace GUI
{
	////////////////////////////////////////////////////////////////////////////////////////////
	////////	VertexBuffer	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	#pragma region VertexBuffer

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, int size) 
	{
		GLCall(glGenBuffers(1, &m_RendererId));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_RendererId));
	}

	void OpenGLVertexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
	#pragma endregion VertexBuffer

	////////////////////////////////////////////////////////////////////////////////////////////
	////////	IndexBuffer		////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	#pragma region IndexBuffer

	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* vertices, int count)
		: m_RendererId(0), m_Count(count)
	{
		GLCall(glGenBuffers(1, &m_RendererId));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), vertices, GL_STATIC_DRAW));
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_RendererId));
	}

	void OpenGLIndexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	#pragma endregion IndexBuffer

}
