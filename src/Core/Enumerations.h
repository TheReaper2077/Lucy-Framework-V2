#pragma once

namespace lf {
	enum Projection {
		ORTHOGRAPHIC,
		PERSPECTIVE,

		Projection_COUNT
	};

	enum Primitive {
		POINT,
		LINE,
		LINE_STRIP,
		TRIANGLE,
		TRIANGLE_FAN,
		TRIANGLE_STRIP,

		Primitive_COUNT
	};

	enum CameraType {
		FPS,
		TPS,
		Default,
		None,

		CameraType_COUNT
	};
	
	enum ForceMode {
		Impulse,
		Acceleration,
		Force,
		VelocityChange,

		ForceMode_COUNT
	};

	enum LightMode {
		Point = 0,
		Spot,
		Area,
		Directional,

		LightMode_COUNT
	};

	enum MaterialAttrib {
		Ambient_Color,
		Diffuse_Color,
		Specular_Color,
		Ambient_Texture,
		Diffuse_Texture,
		Specular_Texture,
		Shininess_Float,

		MaterialAttrib_COUNT
	};

	enum DrawMode {
		NONE = 0,
		INDIRECT,
		INSTANCED,
		INSTANCED_BASEINSTANCE,
		
		INDEXED,
		INDEXED_INDIRECT,
		INDEXED_INSTANCED,
		INDEXED_BASEVERTEX,
		INDEXED_INSTANCED_BASEINSTANCE,
		INDEXED_INSTANCED_BASEVERTEX,
		INDEXED_INSTANCED_BASEVERTEX_BASEINSTANCE,

		RANGE_INDEXED,
		RANGE_INDEXED_BASEVERTEX,

		PIXELS,

		DrawMode_COUNT
	};
}