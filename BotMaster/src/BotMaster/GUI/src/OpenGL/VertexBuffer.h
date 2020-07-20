#pragma once

#include "src/Base.h"

class VertexBuffer
{
public:
	VertexBuffer()
		: m_Id(0) {}
	VertexBuffer(const void* data, int size, unsigned int usage);
	~VertexBuffer();

	inline unsigned int getId() const { return m_Id; };
	void Data(const void* data, int size, unsigned int usage);
	void bind() const;
	void unbind() const;

private:
	unsigned int m_Id;
};