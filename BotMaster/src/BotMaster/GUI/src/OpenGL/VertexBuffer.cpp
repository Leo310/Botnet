#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, int size, unsigned int usage)
	: m_Id(0)
{
	Data(data, size, usage);
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_Id));
}


void VertexBuffer::Data(const void* data, int size, unsigned int usage)
{
	GLCall(glGenBuffers(1, &m_Id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Id));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));

}

void VertexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Id));
}

void VertexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
