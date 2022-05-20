#include <RenderAPI.h>

Texture::Texture() {
	glGenTextures(1, &id);
}

Texture::~Texture() {
	glDeleteTextures(1, &id);
}

Texture::Texture(const char* filename) {
	glGenTextures(1, &id);
	
	this->Bind();
	this->filename = std::string(filename);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenerateMipmap(this->id);

	int width, height, channels;
	unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);

	assert(data);

	if (channels == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	if (channels == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	
	stbi_image_free(data);

	this->UnBind();

	this->channels = channels;
	this->width = width;
	this->height = height;
}

void Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, this->id);
}

void Texture::BindUnit(uint32_t unit) {
	glBindTextureUnit(unit, this->id);
}

void Texture::UnBind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}
