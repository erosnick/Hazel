#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Platform/OpenGL/VertexBuffer.h"
#include "Platform/OpenGL/IndexBuffer.h"
#include "Platform/OpenGL/VertexArray.h"
#include "Platform/OpenGL/Shader.h"

namespace Hazel
{
	class Drawable
	{
	public:

		virtual void initialize()
		{
			VertexBufferLayout layout;
			layout.Push<float>(3);
			layout.Push<float>(2);
			layout.Push<float>(4);

			vertexArray.initiliaze();

			vertexBuffer = VertexBuffer(vertices.data(), static_cast<uint32_t>(sizeof(Vertex) * vertices.size()));
			indexBuffer = IndexBuffer(indices.data(), static_cast<uint32_t>(indices.size()));

			vertexArray.AddBuffer(vertexBuffer, layout);
		}

		virtual void preDraw()
		{
			vertexArray.Bind();
		}

		int VertexCount() const
		{
			return vertices.size();
		}

		int IndexCount() const
		{
			return indices.size();
		}

	protected:

		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;

		uint32_t vao = 0;
		VertexArray vertexArray;
	};

	class Triangle : public Drawable
	{
	public:

		Triangle()
		{
			vertices = {
				Vertex{-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
				Vertex{ 0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f},
				Vertex{ 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f}
			};

			indices = {
				0, 1, 2
			};
		}
	};

	class Rectangle : public Drawable
	{
	public:

		Rectangle()
		{
			vertices = {
				Vertex{-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
				Vertex{-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f},
				Vertex{ 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
				Vertex{ 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f}
			};

			indices = {
				0, 1, 2,
				0, 2, 3
			};
		}
	};

	class Renderer
	{
	public:

		void Clear(float r, float g, float b, float a = 1.0f) const;
		void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const;
		void Draw(const Drawable& drawable);
	};
}