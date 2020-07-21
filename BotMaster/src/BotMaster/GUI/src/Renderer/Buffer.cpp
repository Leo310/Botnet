#include "BMpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform - API/OpenGL/OpenGLBuffer.h"

namespace GUI
{
	////////////////////////////////////////////////////////////////////////////////////////////
	////////	VertexBuffer	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	VertexBuffer* VertexBuffer::Create(float* vertices, int size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::NONE:
			assert(false, "RendererAPI::NONE is currently not supported");
			return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		assert(false, "Unknown RendererAPI");
		return nullptr;
	}

	////////////////////////////////////////////////////////////////////////////////////////////
	////////	IndexBuffer		////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	IndexBuffer* IndexBuffer::Create(unsigned int* indices, int count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::NONE:
			assert(false, "RendererAPI::NONE is currently not supported");
			return nullptr;
		case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
		}

		assert(false, "Unknown RendererAPI");
		return nullptr;
	}
}
