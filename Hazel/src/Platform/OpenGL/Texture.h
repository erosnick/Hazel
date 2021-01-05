#pragma once
class Texture
{
public:

	Texture(std::string& path);
	~Texture();

	void Bind(uint32_t slot = 0) const;
	void Unbind() const;

	inline uint32_t Width() const { return width; }
	inline uint32_t Height() const { return height; }

private:

	uint32_t width;
	uint32_t height;
};

