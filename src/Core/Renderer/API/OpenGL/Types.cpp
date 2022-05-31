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
		{ lgl::UNSIGNED_INT_24_8, GL_UNSIGNED_INT_24_8 },
	};

	return TypeMap_[type];
}

const unsigned int lgl::GetMap(const Format format) {
	static std::unordered_map<Format, unsigned int> FormatMap_ = {
		{ lgl::RGB, GL_RGB },
		{ lgl::RGBA, GL_RGBA },
		{ lgl::RGBA32F, GL_RGBA32F },
		{ lgl::RGB32F, GL_RGB32F },
		{ lgl::RGBA16F, GL_RGBA16F },
		{ lgl::RGB16F, GL_RGB16F },
		{ lgl::DEPTH_STENCIL, GL_DEPTH_STENCIL },
		{ lgl::DEPTH24_STENCIL8, GL_DEPTH24_STENCIL8 },
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

const unsigned int lgl::GetMap(const Attachment texturemode) {
	static std::unordered_map<Attachment, unsigned int> AttachmentMap_ = {
		{ lgl::COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT0 },
		{ lgl::COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT1 },
		{ lgl::COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT2 },
		{ lgl::COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT3 },
		{ lgl::COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT4 },
		{ lgl::COLOR_ATTACHMENT5, GL_COLOR_ATTACHMENT5 },
		{ lgl::COLOR_ATTACHMENT6, GL_COLOR_ATTACHMENT6 },
		{ lgl::COLOR_ATTACHMENT7, GL_COLOR_ATTACHMENT7 },
		{ lgl::COLOR_ATTACHMENT8, GL_COLOR_ATTACHMENT8 },
		{ lgl::COLOR_ATTACHMENT9, GL_COLOR_ATTACHMENT9 },
		{ lgl::COLOR_ATTACHMENT10, GL_COLOR_ATTACHMENT10 },
		{ lgl::COLOR_ATTACHMENT11, GL_COLOR_ATTACHMENT11 },
		{ lgl::COLOR_ATTACHMENT12, GL_COLOR_ATTACHMENT12 },
		{ lgl::COLOR_ATTACHMENT13, GL_COLOR_ATTACHMENT13 },
		{ lgl::COLOR_ATTACHMENT14, GL_COLOR_ATTACHMENT14 },
		{ lgl::COLOR_ATTACHMENT15, GL_COLOR_ATTACHMENT15 },
		{ lgl::COLOR_ATTACHMENT16, GL_COLOR_ATTACHMENT16 },
		{ lgl::COLOR_ATTACHMENT17, GL_COLOR_ATTACHMENT17 },
		{ lgl::COLOR_ATTACHMENT18, GL_COLOR_ATTACHMENT18 },
		{ lgl::COLOR_ATTACHMENT19, GL_COLOR_ATTACHMENT19 },
		{ lgl::COLOR_ATTACHMENT20, GL_COLOR_ATTACHMENT20 },
		{ lgl::COLOR_ATTACHMENT21, GL_COLOR_ATTACHMENT21 },
		{ lgl::COLOR_ATTACHMENT22, GL_COLOR_ATTACHMENT22 },
		{ lgl::COLOR_ATTACHMENT23, GL_COLOR_ATTACHMENT23 },
		{ lgl::COLOR_ATTACHMENT24, GL_COLOR_ATTACHMENT24 },
		{ lgl::COLOR_ATTACHMENT25, GL_COLOR_ATTACHMENT25 },
		{ lgl::COLOR_ATTACHMENT26, GL_COLOR_ATTACHMENT26 },
		{ lgl::COLOR_ATTACHMENT27, GL_COLOR_ATTACHMENT27 },
		{ lgl::COLOR_ATTACHMENT28, GL_COLOR_ATTACHMENT28 },
		{ lgl::COLOR_ATTACHMENT29, GL_COLOR_ATTACHMENT29 },
		{ lgl::COLOR_ATTACHMENT30, GL_COLOR_ATTACHMENT30 },
		{ lgl::COLOR_ATTACHMENT31, GL_COLOR_ATTACHMENT31 },
		{ lgl::DEPTH_ATTACHMENT, GL_DEPTH_ATTACHMENT },
		{ lgl::STENCIL_ATTACHMENT, GL_STENCIL_ATTACHMENT },
		{ lgl::DEPTH_STENCIL_ATTACHMENT, GL_DEPTH_STENCIL_ATTACHMENT },
	};

	return AttachmentMap_[texturemode];
}