#pragma once

#include "Renderer.h"

class VertexBuffer
{
public:

	VertexBuffer() {}
	VertexBuffer(const void* data, uint32_t size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:

	uint32_t rendererID = 0;
};