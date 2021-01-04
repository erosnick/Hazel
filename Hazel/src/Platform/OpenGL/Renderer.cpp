#include "HazelPCH.h"
#include "Renderer.h"
#include "Hazel/Log.h"

namespace Hazel
{
	void Renderer::Clear(float r, float g, float b, float a) const
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const
	{
		vertexArray.Bind();
		indexBuffer.Bind();
	}

	void Renderer::Draw(const Drawable& drawable)
	{

	}
}