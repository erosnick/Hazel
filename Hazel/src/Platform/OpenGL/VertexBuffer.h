#pragma once

struct Vertex
{
	float x;
	float y;
	float z;
	float u;
	float v;
	float r;
	float g;
	float b;
	float a;
};

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

