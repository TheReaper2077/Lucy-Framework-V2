#ifndef STB_IMAGE_IMPLEMENTATION
	#define STB_IMAGE_IMPLEMENTATION
#endif

#include <stb_image.h>
#include <LucyGL/Texture.h>

#include <glad/glad.h>
#include <iostream>

lgl::Texture::Texture(TextureMode mode) {
	texture_mode = GetMap(mode);

	glGenTextures(1, &id);
}

lgl::Texture::~Texture() {
	glDeleteTextures(1, &id);
}

void lgl::Texture::LoadFile(const char* filename) {
	Bind();

	SetWrapMode(WrapMode_MIRRORED_REPEAT, WrapMode_MIRRORED_REPEAT);
	SetFilteringMode(FilterMode_NEAREST, FilterMode_NEAREST);

	auto* data = stbi_load(filename, &width, &height, &channels, 0);
		
	if (!data) {
		static uint8_t default_data[] = {
			255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255,
			  0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,
			255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255,
			  0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,
			255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255,
			  0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,
			255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255,
			  0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,
			255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255,
			  0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,
			255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255,
			  0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,
			255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255,
			  0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,
			255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255,
			  0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,
		};

		glTexImage2D(texture_mode, 0, GL_RGBA, 4, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, default_data);
	} else {
		if (channels == 4) glTexImage2D(texture_mode, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		if (channels == 3) glTexImage2D(texture_mode, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}

	stbi_image_free(data);

	UnBind();
}

void lgl::Texture::GenerateMimmap() {
	Bind();
	glGenerateMipmap(id);
}

void lgl::Texture::SetWrapMode(TextureWrapMode wrap_s, TextureWrapMode wrap_t, TextureWrapMode wrap_r) {
	Bind();
	if (this->wrap_s != wrap_s && wrap_s != WrapMode_None) {
		this->wrap_s = wrap_s;
		glTexParameteri(texture_mode, GL_TEXTURE_WRAP_S, GetMap(wrap_s));
	}
	if (this->wrap_t != wrap_t && wrap_t != WrapMode_None) {
		this->wrap_t = wrap_t;
		glTexParameteri(texture_mode, GL_TEXTURE_WRAP_T, GetMap(wrap_t));
	}
	if (this->wrap_r != wrap_r && wrap_r != WrapMode_None) {
		this->wrap_r = wrap_r;
		glTexParameteri(texture_mode, GL_TEXTURE_WRAP_R, GetMap(wrap_r));
	}
}

void lgl::Texture::SetFilteringMode(TextureFilteringMode mag, TextureFilteringMode min) {
	Bind();
	if (this->mag != mag && mag != FilterMode_None) {
		this->mag = mag;
		glTexParameteri(texture_mode, GL_TEXTURE_MAG_FILTER, GetMap(mag));
	}
	if (this->min != min && min != FilterMode_None) {
		this->min = min;
		glTexParameteri(texture_mode, GL_TEXTURE_MIN_FILTER, GetMap(min));
	}
}

void lgl::Texture::Bind() {
	glBindTexture(texture_mode, this->id);
}

void lgl::Texture::BindUnit(unsigned int unit) {
	glBindTextureUnit(unit, this->id);
}

void lgl::Texture::UnBind() {
	glBindTexture(texture_mode, 0);
}
