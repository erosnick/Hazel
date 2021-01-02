#pragma once

#include "HazelPCH.h"
#include <glad/glad.h>

namespace Hazel
{
	struct VertexBufferElement
	{
		uint32_t type;
		uint32_t count;
		unsigned char normalized;

		static uint32_t GetTypeSize(uint32_t type)
		{
			switch (type)
			{
				case GL_FLOAT:		return 4;
				case GL_UNSIGNED_INT: return 4;
				case GL_UNSIGNED_BYTE: return 1;
				default:
					break;
			}

			return 0;
		}
	};

	class VertexBufferLayout
	{
	public:

		VertexBufferLayout() {}

		template<typename T>
		void Push(uint32_t count)
		{

		}

		template<>
		void Push<float>(uint32_t count)
		{
			elements.push_back({ GL_FLOAT, count, GL_FALSE });
			stride += VertexBufferElement::GetTypeSize(GL_FLOAT) * count;
		}

		template<>
		void Push<uint32_t>(uint32_t count)
		{
			elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			stride += VertexBufferElement::GetTypeSize(GL_UNSIGNED_INT) * count;
		}

		template<>
		void Push<unsigned char>(uint32_t count)
		{
			elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
			stride += VertexBufferElement::GetTypeSize(GL_UNSIGNED_BYTE);
		}

		inline const std::vector<VertexBufferElement>& GetElements() const { return elements; }
		inline uint32_t GetStride() const { return stride; }

	private:

		std::vector<VertexBufferElement> elements;

		uint32_t stride = 0;
	};
}
