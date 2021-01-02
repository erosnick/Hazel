#include "HazelPCH.h"

#include "VertexArray.h"

namespace Hazel
{
	VertexArray::VertexArray()
	{

	}

	VertexArray::~VertexArray()
	{
		//GLCall(glDeleteBuffers(1, &rendererID));
	}

	void VertexArray::initiliaze()
	{
		GLCall(glGenVertexArrays(1, &rendererID));
		Bind();
	}

	void VertexArray::AddBuffer(VertexBuffer& inVertexBuffer, const VertexBufferLayout& layout)
	{
		vertexBuffer = std::move(inVertexBuffer);

		const auto& elements = layout.GetElements();
		uint32_t offset = 0;
		for (uint32_t i = 0; i < elements.size(); i++)
		{
			const auto& element = elements[i];

			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
			offset += element.count * VertexBufferElement::GetTypeSize(element.type);
		}
	}

	void VertexArray::Bind() const
	{
		GLCall(glBindVertexArray(rendererID));
	}

	void VertexArray::Unbind() const
	{
		GLCall(glBindVertexArray(0));
	}
}