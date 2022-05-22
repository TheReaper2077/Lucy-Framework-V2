#pragma once

namespace lgl {
	typedef unsigned int FrameBufferId;

	struct FrameBuffer {
		FrameBuffer(int width, int height, bool picking = false);
		~FrameBuffer();

		FrameBufferId id;
		int index;
		int width, height;

		unsigned int picking;
		unsigned int texture;

		void Bind();
		void UnBind();
	};
}