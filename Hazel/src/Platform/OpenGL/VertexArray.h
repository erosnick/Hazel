#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Hazel
{
	class VertexArray
	{
	public:

		VertexArray();
		~VertexArray();

		void initiliaze();

		void AddBuffer(VertexBuffer& inVertexBuffer, const VertexBufferLayout& layout);

		void Bind() const;
		void Unbind() const;

	private:

		VertexBuffer vertexBuffer;
		uint32_t rendererID = 0;
	};
}