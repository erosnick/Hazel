#pragma once

#include "Renderer.h"

namespace Hazel
{
	class IndexBuffer
	{
	public:

		IndexBuffer() {}
		IndexBuffer(const uint32_t* data, uint32_t inCount);
		IndexBuffer(const IndexBuffer&& indexBuffer) noexcept;
		IndexBuffer& operator=(const IndexBuffer& indexBuffer) noexcept;

		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		inline uint32_t Count() const { return count; }

	private:

		uint32_t rendererID = 0;
		uint32_t count = 0;
	};
}