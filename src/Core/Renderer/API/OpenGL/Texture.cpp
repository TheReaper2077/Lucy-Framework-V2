#ifndef STB_IMAGE_IMPLEMENTATION
	#define STB_IMAGE_IMPLEMENTATION
#endif

#include <stb_image.h>
#include <GraphicsAPI/Texture.h>

#include <glad/glad.h>

Texture::Texture(unsigned int mode) {
	if (mode == 0)
		texture_mode = GL_TEXTURE_2D;

	glGenTextures(1, &id);
}

Texture::~Texture() {
	glDeleteTextures(1, &id);
}

void Texture::LoadFile(const char* filename) {
	Bind();

	SetWrapMode(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
	SetFilteringMode(GL_LINEAR, GL_LINEAR);
	GenerateMimmap();
	
	unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);

	assert(data);

	if (channels == 4)
		glTexImage2D(texture_mode, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	if (channels == 3)
		glTexImage2D(texture_mode, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	
	stbi_image_free(data);

	UnBind();
}

void Texture::GenerateMimmap() {
	Bind();
	glGenerateMipmap(id);
	UnBind();
}

void Texture::SetWrapMode(unsigned int wrap_s, unsigned int wrap_t, unsigned int wrap_r) {
	Bind();
	if (wrap_s)
		glTexParameteri(texture_mode, GL_TEXTURE_WRAP_S, wrap_s);
	if (wrap_t)
		glTexParameteri(texture_mode, GL_TEXTURE_WRAP_T, wrap_t);
	if (wrap_r)
		glTexParameteri(texture_mode, GL_TEXTURE_WRAP_R, wrap_r);
	UnBind();
}

void Texture::SetFilteringMode(unsigned int mag, unsigned int min) {
	Bind();
	if (mag)
		glTexParameteri(texture_mode, GL_TEXTURE_MAG_FILTER, mag);
	if (min)
		glTexParameteri(texture_mode, GL_TEXTURE_MIN_FILTER, min);
	UnBind();
}

void Texture::Bind() {
	glBindTexture(texture_mode, this->id);
}

void Texture::BindUnit(unsigned int unit) {
	glBindTextureUnit(unit, this->id);
}

void Texture::UnBind() {
	glBindTexture(texture_mode, 0);
}
