#pragma once

#include "Renderer.h"

class IndexBuffer
{
public:

	IndexBuffer() {}
	IndexBuffer(const void* data, uint32_t size, uint32_t inCount);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline uint32_t Count() const { return count; }

private:

	uint32_t rendererID = 0;
	uint32_t count = 0;
};