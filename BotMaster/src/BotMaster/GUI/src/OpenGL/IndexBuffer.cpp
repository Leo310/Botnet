#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const void* data, int size, unsigned int usage)
	: m_Id(0), m_Count(0)
{
		Data(data, size, usage);
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_Id));
}

void IndexBuffer::Data(const void* data, int size, unsigned int usage)
{
	GLCall(glGenBuffers(1, &m_Id));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage));
	m_Count = size / sizeof(unsigned int);
}

void IndexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Id));
}

void IndexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
