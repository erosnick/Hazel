#pragma once

#include "Renderer.h"

namespace Hazel
{
	class VertexBuffer
	{
	public:

		VertexBuffer();
		VertexBuffer(const Vertex* data, uint32_t size);
		VertexBuffer(const VertexBuffer&& vertexBuffer) noexcept;

		VertexBuffer& operator=(const VertexBuffer&& vertexBuffer) noexcept;

		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

	private:

		uint32_t rendererID = 0;
	};
}

