#include "HazelPCH.h"
#include "VertexBuffer.h"
#include "Renderer.h"
#include "Hazel/Log.h"

namespace Hazel
{
	VertexBuffer::VertexBuffer()
	{
	}

	VertexBuffer::VertexBuffer(const Vertex* data, uint32_t size)
	{
		GLCall(glGenBuffers(1, &rendererID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	VertexBuffer::VertexBuffer(const VertexBuffer&& vertexBuffer) noexcept
	{
		rendererID = vertexBuffer.rendererID;
	}

	VertexBuffer& VertexBuffer::operator=(const VertexBuffer&& vertexBuffer) noexcept
	{
		rendererID = vertexBuffer.rendererID;

		return *this;
	}

	VertexBuffer::~VertexBuffer()
	{
		//GLCall(glDeleteBuffers(1, &rendererID));
	}

	void VertexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
	}

	void VertexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

}