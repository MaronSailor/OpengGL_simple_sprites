#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture::Texture()
{
	glGenTextures(1, &textureId);


}

void Texture::loadTexture(const GLchar* texPath)
{
	int width, height, nrchannels;

	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);

	auto image = stbi_load(texPath, &width, &height, &nrchannels, STBI_rgb_alpha);

	if (!image) {
		std::cerr << "ERROR: could not load texture -> " << texPath << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "Image " << texPath << " was loaded\n";

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, nrchannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	this->textureWidth = width / horizontalFrameCount;
	this->textureHeight = height / verticalFrameCount;

	stbi_image_free(image);
}

void Texture::bindTexture()
{
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureId);
}