#pragma once

#include <string>
#include <LucyGL/Texture.h>

namespace lucy {
	namespace Component {
		struct TextureRaw {
			std::string id;
			std::string filename;
			std::string name;

			lgl::Texture* texture;
		};
	}
}