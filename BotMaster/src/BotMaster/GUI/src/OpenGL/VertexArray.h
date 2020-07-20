#pragma once

#include "src/Base.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

class VertexArray
{
public:
	VertexArray()
		: m_Id(0) {};
	VertexArray(bool bind);
	~VertexArray();

	void generate();
	void bind();
	void unbind();

	void addBuffer(const VertexBuffer& vb,const VertexBufferLayout& layout);

private:
	unsigned int m_Id;
};