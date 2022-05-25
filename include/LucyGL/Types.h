#pragma once

namespace lgl {
	enum Type {
		BYTE,
		UNSIGNED_BYTE,
		SHORT,
		UNSIGNED_SHORT,
		INT,
		UNSIGNED_INT,
		FLOAT,
	};

	const unsigned int GetMap(const Type type);

	enum Format {
		RGB,
		RGBA,
	};

	const unsigned int GetMap(const Format format);

	enum Primitive {
		POINT,
		LINE,
		TRIANGLE,
		LINE_STRIP,
		TRIANGLE_FAN,
		TRIANGLE_STRIP,
	};

	const unsigned int GetMap(const Primitive primitive);

	enum TextureFilteringMode {
		FilterMode_None = 0,
		FilterMode_LINEAR,
		FilterMode_NEAREST,
	};

	const unsigned int GetMap(const TextureFilteringMode texturefilteringmode);

	enum TextureWrapMode {
		WrapMode_None = 0,
		WrapMode_CLAMP_TO_EDGE,
		WrapMode_CLAMP_TO_BORDER,
		WrapMode_MIRRORED_REPEAT,
		WrapMode_REPEAT,
		WrapMode_MIRROR_CLAMP_TO_EDGE,
	};

	const unsigned int GetMap(const TextureWrapMode texturewrapmode);

	enum TextureMode {
		TEXTURE_1D,
		TEXTURE_2D,
		TEXTURE_3D,
		TEXTURE_1D_ARRAY,
		TEXTURE_2D_ARRAY,
		TEXTURE_RECTANGLE,
		TEXTURE_CUBE_MAP,
		TEXTURE_CUBE_MAP_ARRAY,
		TEXTURE_BUFFER,
		TEXTURE_2D_MULTISAMPLE,
		TEXTURE_2D_MULTISAMPLE_ARRAY,
	};

	const unsigned int GetMap(const TextureMode texturemode);
}