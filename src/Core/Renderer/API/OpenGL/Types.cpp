#include <GraphicsAPI/Types.h>
#include <glad/glad.h>
#include <unordered_map>

unsigned int lgl::GetTypeMap(const Type type) {
	static std::unordered_map<Type, unsigned int> TypeMap_ = {
		{ BYTE, GL_BYTE },
		{ UNSIGNED_BYTE, GL_UNSIGNED_BYTE },
		{ SHORT, GL_SHORT },
		{ UNSIGNED_SHORT, GL_UNSIGNED_SHORT },
		{ INT, GL_INT },
		{ UNSIGNED_INT, GL_UNSIGNED_INT },
		{ FLOAT, GL_FLOAT },
	};

	return TypeMap_[type];
}

unsigned int lgl::GetMap(const Format format) {
	static std::unordered_map<Format, unsigned int> FormatMap_ = {
		{ RGB, GL_RGB },
		{ RGBA, GL_RGBA },
	};

	return FormatMap_[format];
}

unsigned int lgl::GetMap(const Primitive primitive) {
	static std::unordered_map<Primitive, unsigned int> PrimitiveMap_ = {
		{ POINT, GL_POINT },
		{ POINTS, GL_POINTS },
		{ LINE, GL_LINE },
		{ LINES, GL_LINES },
		{ LINE_STRIP, GL_LINE_STRIP },
		{ TRIANGLES, GL_TRIANGLES },
		{ TRIANGLE_FAN, GL_TRIANGLE_FAN },
		{ TRIANGLE_STRIP, GL_TRIANGLE_STRIP },
	};

	return PrimitiveMap_[primitive];
}

unsigned int lgl::GetMap(const TextureFilteringMode texturefilteringmode) {
	static std::unordered_map<TextureFilteringMode, unsigned int> TextureFilteringModeMap_ = {
		{ FilterMode_LINEAR, GL_LINEAR },
		{ FilterMode_NEAREST, GL_NEAREST },
	};

	return TextureFilteringModeMap_[texturefilteringmode];
}

unsigned int lgl::GetMap(const TextureWrapMode texturewrapmode) {
	static std::unordered_map<TextureWrapMode, unsigned int> TextureWrapModeMap_ = {
		{ WrapMode_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE },
		{ WrapMode_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER },
		{ WrapMode_MIRRORED_REPEAT, GL_MIRRORED_REPEAT },
		{ WrapMode_REPEAT, GL_REPEAT },
		{ WrapMode_MIRROR_CLAMP_TO_EDGE, GL_MIRROR_CLAMP_TO_EDGE },
	};

	return TextureWrapModeMap_[texturewrapmode];
}

unsigned int lgl::GetMap(const TextureMode texturemode) {
	static std::unordered_map<TextureMode, unsigned int> TextureModeMap_ = {
		{ TEXTURE_1D, GL_TEXTURE_1D },
		{ TEXTURE_2D, GL_TEXTURE_2D },
		{ TEXTURE_3D, GL_TEXTURE_3D },
		{ TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY },
		{ TEXTURE_2D_ARRAY, GL_TEXTURE_2D_ARRAY },
		{ TEXTURE_RECTANGLE, GL_TEXTURE_RECTANGLE },
		{ TEXTURE_CUBE_MAP, GL_TEXTURE_CUBE_MAP },
		{ TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_CUBE_MAP_ARRAY },
		{ TEXTURE_BUFFER, GL_TEXTURE_BUFFER },
		{ TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE },
		{ TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_2D_MULTISAMPLE_ARRAY },
	};

	return TextureModeMap_[texturemode];
}
