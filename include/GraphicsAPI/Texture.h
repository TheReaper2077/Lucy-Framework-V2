#pragma once

typedef unsigned int TextureId;

enum TextureFilteringMode_ {
	TextureFilteringMode_None,
	TextureFilteringMode_LINEAR,
	TextureFilteringMode_NEAREST,
	TextureFilteringMode_COUNT
};

enum TextureWrapMode_ {
	TextureWrapMode_None,
	TextureWrapMode_CLAMP_TO_EDGE,
	TextureWrapMode_CLAMP_TO_BORDER,
	TextureWrapMode_MIRRORED_REPEAT,
	TextureWrapMode_REPEAT,
	TextureWrapMode_MIRROR_CLAMP_TO_EDGE,
	TextureWrapMode_COUNT
};

enum TextureMode_ {
	TextureMode_None,
	TextureMode_TEXTURE_1D,
	TextureMode_TEXTURE_2D,
	TextureMode_TEXTURE_3D,
	TextureMode_TEXTURE_1D_ARRAY,
	TextureMode_TEXTURE_2D_ARRAY,
	TextureMode_TEXTURE_RECTANGLE,
	TextureMode_TEXTURE_CUBE_MAP,
	TextureMode_TEXTURE_CUBE_MAP_ARRAY,
	TextureMode_TEXTURE_BUFFER,
	TextureMode_TEXTURE_2D_MULTISAMPLE,
	TextureMode_TEXTURE_2D_MULTISAMPLE_ARRAY,
	TextureMode_COUNT
};

struct Texture {
	TextureId id;

	int width, height, channels;
	int texture_mode;

	Texture(unsigned int mode = 0);
	~Texture();

	void LoadFile(const char* filename);
	void LoadSpriteSheet(const char* filename, int x, int y, int w, int h);

	void GenerateMimmap();
	void SetWrapMode(unsigned int wrap_s = 0, unsigned int wrap_t = 0, unsigned int wrap_r = 0);
	void SetFilteringMode(unsigned int mag = 0, unsigned int min = 0);

	void Bind();
	void BindUnit(unsigned int unit);
	void UnBind();
};
