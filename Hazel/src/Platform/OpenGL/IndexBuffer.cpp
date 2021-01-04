#include "HazelPCH.h"
#include "IndexBuffer.h"
#include "Utils.h"

namespace Hazel
{
	IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t inCount)
		:count(inCount)
	{
		GLCall(glGenBuffers(1, &rendererID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * count, data, GL_STATIC_DRAW));
	}

	IndexBuffer::IndexBuffer(const IndexBuffer&& indexBuffer) noexcept
	{
		rendererID = indexBuffer.rendererID;
	}

	IndexBuffer& IndexBuffer::operator=(const IndexBuffer& indexBuffer) noexcept
	{
		rendererID = indexBuffer.rendererID;

		return *this;
	}

	IndexBuffer::~IndexBuffer()
	{
		//GLCall(glDeleteBuffers(1, &rendererID));
	}

	void IndexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
	}

	void IndexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

}