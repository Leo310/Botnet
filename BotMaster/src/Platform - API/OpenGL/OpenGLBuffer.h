#pragma once


#include "src/Renderer/Buffer.h"

namespace GUI
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, int size);
		virtual ~OpenGLVertexBuffer();

		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };
		virtual const BufferLayout& GetLayout() const override { return m_Layout; };

		virtual void Bind() const override;
		virtual void Unbind() const override;
	
	private:
		unsigned int m_RendererId;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int* vertices, int count);
		virtual ~OpenGLIndexBuffer();

		inline virtual unsigned int GetCount() const override { return m_Count; }

		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:
		unsigned int m_RendererId;
		unsigned int m_Count;
	};
}

