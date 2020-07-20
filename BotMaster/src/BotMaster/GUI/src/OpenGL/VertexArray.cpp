#include "VertexArray.h"

VertexArray::VertexArray(bool bind)
	: m_Id(0)
{
	if (bind)
	{
		generate();
	}
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_Id));
}

void VertexArray::generate()
{
	GLCall(glGenVertexArrays(1, &m_Id));
	GLCall(glBindVertexArray(m_Id));
}

void VertexArray::bind()
{
	GLCall(glBindVertexArray(m_Id));
}

void VertexArray::unbind()
{
	GLCall(glBindVertexArray(0));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	int offset = 0;
	vb.bind();
	std::vector<Elements> elements = layout.getElements();
	for (int i = 0; i < elements.size(); i++)
	{
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalized, layout.getStride(), (const void*)offset));
		offset += elements[i].count * Elements::getTypeSize(elements[i].type);
	}

}
