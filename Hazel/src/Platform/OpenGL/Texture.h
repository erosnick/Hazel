#pragma once

namespace Hazel
{
	class Texture
	{
	public:

		Texture();
		~Texture();

		void Load(const std::string& path);

		void Bind(uint32_t slot = 0) const;
		void Unbind() const;

		inline uint32_t Width() const { return width; }
		inline uint32_t Height() const { return height; }

	private:

		uint32_t rendererID;
		std::string path;
		unsigned char* buffer;
		int bpp;
		int width;
		int height;
	};
}