#pragma once

#define GL_API
#define GL_ASSERT(x) assert(x)

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <glad/glad.h>
#include <assert.h>
#include <stb_image.h>

#define POSITION_ATTRIB_BIT ( 1 << VertexArrayAttrib::position )
#define NORMAL_ATTRIB_BIT ( 1 << VertexArrayAttrib::normal )
#define COLOR_ATTRIB_BIT ( 1 << VertexArrayAttrib::color )
#define UV0_ATTRIB_BIT ( 1 << VertexArrayAttrib::uv0 )
#define UV1_ATTRIB_BIT ( 1 << VertexArrayAttrib::uv1 )
#define UV2_ATTRIB_BIT ( 1 << VertexArrayAttrib::uv2 )
#define UV3_ATTRIB_BIT ( 1 << VertexArrayAttrib::uv3 )
#define UV4_ATTRIB_BIT ( 1 << VertexArrayAttrib::uv4 )
#define UV5_ATTRIB_BIT ( 1 << VertexArrayAttrib::uv5 )
#define UV6_ATTRIB_BIT ( 1 << VertexArrayAttrib::uv6 )
#define UV7_ATTRIB_BIT ( 1 << VertexArrayAttrib::uv7 )

typedef unsigned int VertexArrayId;
typedef unsigned int VertexBufferId;
typedef unsigned int IndexBufferId;
typedef unsigned int UniformBufferId;
typedef unsigned int ShaderId;
typedef unsigned int TextureId;
typedef unsigned int SpriteAtlasId;
typedef unsigned int FrameBufferId;
typedef unsigned int TextureColorBufferId;
typedef unsigned int RenderBufferId;

struct VertexArrayAttribDescriptor;
struct VertexArray;
struct VertexBuffer;
struct IndexBuffer;
struct UniformBuffer;
struct Shader;
struct Texture;
struct TextureArray2D;
struct FrameBuffer;

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

enum VertexArrayAttrib {
	position = 0,
	normal,
	color,
	uv0,
	uv1,
	uv2,
	uv3,
	uv4,
	uv5,
	uv6,
	uv7,

	VertexArrayAttrib_COUNT
};

struct VertexArrayAttribDescriptor {
	VertexArrayAttrib attr_type;
	unsigned int idx;
	unsigned int size;
	unsigned int type;

	VertexArrayAttribDescriptor(VertexArrayAttrib attr_type, unsigned int idx, unsigned int size, unsigned int type) {
		this->idx = idx;
		this->size = size;
		this->type = type;
		this->attr_type = attr_type;
	}
};

struct VertexArray {
	VertexArrayId id;
	std::size_t stride = 0;
	uint32_t elem_stride = 0;

	uint32_t position_offset = 0;
	bool has_position = false;
	uint32_t normal_offset = 0;
	bool has_normal = false;
	uint32_t color_offset = 0;
	bool has_color = false;
	uint32_t uv0_offset = 0;
	bool has_uv0 = false;
	uint32_t uv1_offset = 0;
	bool has_uv1 = false;
	uint32_t uv2_offset = 0;
	bool has_uv2 = false;
	uint32_t uv3_offset = 0;
	bool has_uv3 = false;
	uint32_t uv4_offset = 0;
	bool has_uv4 = false;
	uint32_t uv5_offset = 0;
	bool has_uv5 = false;
	uint32_t uv6_offset = 0;
	bool has_uv6 = false;
	uint32_t uv7_offset = 0;
	bool has_uv7 = false;
	
	VertexArray(std::vector<VertexArrayAttribDescriptor> layouts);
	~VertexArray();

	void Bind();
	void BindVertexBuffer(VertexBuffer* vertexbuffer, std::size_t stride = 0, std::size_t offset = 0);
	void BindIndexBuffer(IndexBuffer* indexbuffer);
	void UnBind();
};

enum BufferType {
	STATIC,
	DYNAMIC
};

struct VertexBuffer {
	VertexBufferId id;
	BufferType type;
	std::size_t size = 0;

	VertexBuffer();
	~VertexBuffer();

	void Bind();
	void UnBind();
	void Allocate(std::size_t size);
	void AddDataDynamic(void* data, std::size_t size, std::size_t offset = 0);
	void AddDataStatic(void* data, std::size_t size);
};

struct IndexBuffer {
	IndexBufferId id;
	std::size_t size = 0;
	VertexArray* vertexarray;
	
	IndexBuffer(VertexArray* vertexarray);
	~IndexBuffer();

	void Bind();
	void UnBind();
	void Allocate(std::size_t size);
	void AddData(unsigned int* data, std::size_t size, std::size_t offset = 0);
};

struct UniformBuffer {
	UniformBufferId id;
	std::size_t size = 0;
	
	UniformBuffer();
	~UniformBuffer();

	void Allocate(std::size_t size);
	void AddDataDynamic(void* data, std::size_t size, std::size_t offset = 0);
	void BindRange(unsigned int index, std::size_t size, std::size_t offset = 0);
	void Bind();
	void UnBind();
};

struct Shader {
	ShaderId program;
	std::unordered_map<std::string, unsigned int> uniform_location_map;

	std::string name;

	bool textures = false;
	bool texture_array = false;
	bool material = false;
	bool light = false;
	
	Shader(std::string name, const std::string &vs_filename, const std::string &fs_filename, bool file = true);
	~Shader();

	void Bind();
	void UnBind();

	void BindUniformBlock(std::string name, unsigned int index);
	unsigned int GetUniformLoc(std::string name);

	bool SetUniformi(std::string uniform, int v0);
	bool SetUniformf(std::string uniform, float v0);
	bool SetUniformVec3(std::string uniform, const float* v);
	bool SetUniformVec4(std::string uniform, const float* v);
	bool SetUniformMat4(std::string uniform, const float* matrix);
	bool SetUniformArray(std::string uniform, std::size_t count, const float* v);
};

struct Texture {
	TextureId id;
	std::string type;
	std::string filename;
	uint32_t width, height, channels;

	Texture();
	~Texture();
	Texture(const char* filename);

	void Bind();
	void BindUnit(uint32_t unit);
	void UnBind();
};

struct TextureArray2D {
	Texture texture;

	int tilecount;
	int tileheight;
	int tilewidth;
	int columns;
	
	TextureArray2D(int tilew, int tileh, const char* filename);
	~TextureArray2D();

	void Bind();
	void UnBind();
};
