#pragma once

#include "Types.h"
#include <string>
#include <stddef.h>

namespace lgl {
	typedef unsigned int TextureId;
	
	struct Texture {
		TextureId id;
		TextureMode texture_mode;

		int width, height, channels;

		TextureWrapMode wrap_s = WrapMode_None;
		TextureWrapMode wrap_t = WrapMode_None;
		TextureWrapMode wrap_r = WrapMode_None;
		TextureFilteringMode mag = FilterMode_None;
		TextureFilteringMode min = FilterMode_None;

		Texture(TextureMode mode = TEXTURE_2D);
		~Texture();

		void LoadFile(const char* filename);
		void LoadSpriteSheet(const char* filename, int x, int y, int w, int h);

		void GenerateMimmap();
		void SetWrapMode(TextureWrapMode wrap_s = WrapMode_None, TextureWrapMode wrap_t = WrapMode_None, TextureWrapMode wrap_r = WrapMode_None);
		void SetFilteringMode(TextureFilteringMode mag = FilterMode_None, TextureFilteringMode min = FilterMode_None);

		void Bind();
		void BindUnit(unsigned int unit);
		void UnBind();
	};
}