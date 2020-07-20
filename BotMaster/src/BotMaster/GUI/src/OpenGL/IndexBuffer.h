#pragma once

#include "src/Base.h"

class IndexBuffer
{
public:
	IndexBuffer()
		: m_Id(0), m_Count(0) {}
	IndexBuffer(const void* data, int size, unsigned int usage);
	~IndexBuffer();

	void Data(const void* data, int size, unsigned int usage);

	void bind() const;
	void unbind() const;

	inline unsigned int getCount() const { return m_Count; };

private:
	unsigned int m_Id;

	unsigned int m_Count;
};