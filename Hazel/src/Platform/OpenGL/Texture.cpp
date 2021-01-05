#include "HazelPCH.h"
#include "Texture.h"
#include "Utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Hazel
{
	Texture::Texture()
		: rendererID(0),
		path(""),
		buffer(nullptr),
		bpp(0),
		width(0),
		height(0)
	{

	}

	Texture::~Texture()
	{
		GLCall(glDeleteTextures(1, &rendererID));
	}

	void Texture::Load(const std::string& path)
	{
		GLCall(glGenTextures(1, &rendererID));
		GLCall(glBindTexture(GL_TEXTURE_2D, rendererID));

		stbi_set_flip_vertically_on_load(1);
		buffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer));

		if (buffer != nullptr)
		{
			stbi_image_free(buffer);
		}
	}

	void Texture::Bind(uint32_t slot) const
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + slot))
		GLCall(glBindTexture(GL_TEXTURE_2D, rendererID));
	}

	void Texture::Unbind() const
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}
}