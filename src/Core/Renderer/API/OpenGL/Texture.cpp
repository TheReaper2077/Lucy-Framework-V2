#ifndef STB_IMAGE_IMPLEMENTATION
	#define STB_IMAGE_IMPLEMENTATION
#endif

#include <stb_image.h>
#include <GraphicsAPI/Texture.h>

#include <glad/glad.h>

lfal::Texture::Texture(TextureMode mode) {
	texture_mode = GetMap(mode);

	glGenTextures(1, &id);
}

lfal::Texture::~Texture() {
	glDeleteTextures(1, &id);
}

void lfal::Texture::LoadFile(const char* filename) {
	Bind();

	SetWrapMode(WrapMode_MIRRORED_REPEAT, WrapMode_MIRRORED_REPEAT);
	SetFilteringMode(FilterMode_LINEAR, FilterMode_LINEAR);
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

void lfal::Texture::GenerateMimmap() {
	Bind();
	glGenerateMipmap(id);
	UnBind();
}

void lfal::Texture::SetWrapMode(TextureWrapMode wrap_s, TextureWrapMode wrap_t, TextureWrapMode wrap_r) {
	Bind();
	if (wrap_s != WrapMode_None)
		glTexParameteri(texture_mode, GL_TEXTURE_WRAP_S, GetMap(wrap_s));
	if (wrap_t != WrapMode_None)
		glTexParameteri(texture_mode, GL_TEXTURE_WRAP_T, GetMap(wrap_t));
	if (wrap_r != WrapMode_None)
		glTexParameteri(texture_mode, GL_TEXTURE_WRAP_R, GetMap(wrap_r));
	UnBind();
}

void lfal::Texture::SetFilteringMode(TextureFilteringMode mag, TextureFilteringMode min) {
	Bind();
	if (mag != FilterMode_None)
		glTexParameteri(texture_mode, GL_TEXTURE_MAG_FILTER, GetMap(mag));
	if (min != FilterMode_None)
		glTexParameteri(texture_mode, GL_TEXTURE_MIN_FILTER, GetMap(min));
	UnBind();
}

void lfal::Texture::Bind() {
	glBindTexture(texture_mode, this->id);
}

void lfal::Texture::BindUnit(unsigned int unit) {
	glBindTextureUnit(unit, this->id);
}

void lfal::Texture::UnBind() {
	glBindTexture(texture_mode, 0);
}
