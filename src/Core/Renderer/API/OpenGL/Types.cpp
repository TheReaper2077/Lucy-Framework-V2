#include <LucyGL/Types.h>
#include <glad/glad.h>
#include <unordered_map>

const unsigned int lgl::GetMap(const Type type) {
	static std::unordered_map<Type, unsigned int> TypeMap_ = {
		{ lgl::BYTE, GL_BYTE },
		{ lgl::UNSIGNED_BYTE, GL_UNSIGNED_BYTE },
		{ lgl::SHORT, GL_SHORT },
		{ lgl::UNSIGNED_SHORT, GL_UNSIGNED_SHORT },
		{ lgl::INT, GL_INT },
		{ lgl::UNSIGNED_INT, GL_UNSIGNED_INT },
		{ lgl::FLOAT, GL_FLOAT },
	};

	return TypeMap_[type];
}

const unsigned int lgl::GetMap(const Format format) {
	static std::unordered_map<Format, unsigned int> FormatMap_ = {
		{ lgl::RGB, GL_RGB },
		{ lgl::RGBA, GL_RGBA },
	};

	return FormatMap_[format];
}

const unsigned int lgl::GetMap(const Primitive primitive) {
	static std::unordered_map<Primitive, unsigned int> PrimitiveMap_ = {
		{ lgl::POINT, GL_POINTS },
		{ lgl::LINE, GL_LINES },
		{ lgl::LINE_STRIP, GL_LINE_STRIP },
		{ lgl::TRIANGLE, GL_TRIANGLES },
		{ lgl::TRIANGLE_FAN, GL_TRIANGLE_FAN },
		{ lgl::TRIANGLE_STRIP, GL_TRIANGLE_STRIP },
	};

	return PrimitiveMap_[primitive];
}

const unsigned int lgl::GetMap(const TextureFilteringMode texturefilteringmode) {
	static std::unordered_map<TextureFilteringMode, unsigned int> TextureFilteringModeMap_ = {
		{ lgl::FilterMode_LINEAR, GL_LINEAR },
		{ lgl::FilterMode_NEAREST, GL_NEAREST },
	};

	return TextureFilteringModeMap_[texturefilteringmode];
}

const unsigned int lgl::GetMap(const TextureWrapMode texturewrapmode) {
	static std::unordered_map<TextureWrapMode, unsigned int> TextureWrapModeMap_ = {
		{ lgl::WrapMode_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE },
		{ lgl::WrapMode_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER },
		{ lgl::WrapMode_MIRRORED_REPEAT, GL_MIRRORED_REPEAT },
		{ lgl::WrapMode_REPEAT, GL_REPEAT },
		{ lgl::WrapMode_MIRROR_CLAMP_TO_EDGE, GL_MIRROR_CLAMP_TO_EDGE },
	};

	return TextureWrapModeMap_[texturewrapmode];
}

const unsigned int lgl::GetMap(const TextureMode texturemode) {
	static std::unordered_map<TextureMode, unsigned int> TextureModeMap_ = {
		{ lgl::TEXTURE_1D, GL_TEXTURE_1D },
		{ lgl::TEXTURE_2D, GL_TEXTURE_2D },
		{ lgl::TEXTURE_3D, GL_TEXTURE_3D },
		{ lgl::TEXTURE_1D_ARRAY, GL_TEXTURE_1D_ARRAY },
		{ lgl::TEXTURE_2D_ARRAY, GL_TEXTURE_2D_ARRAY },
		{ lgl::TEXTURE_RECTANGLE, GL_TEXTURE_RECTANGLE },
		{ lgl::TEXTURE_CUBE_MAP, GL_TEXTURE_CUBE_MAP },
		{ lgl::TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_CUBE_MAP_ARRAY },
		{ lgl::TEXTURE_BUFFER, GL_TEXTURE_BUFFER },
		{ lgl::TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE },
		{ lgl::TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_2D_MULTISAMPLE_ARRAY },
	};

	return TextureModeMap_[texturemode];
}
