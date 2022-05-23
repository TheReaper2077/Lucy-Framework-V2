#include <LucyGL/DrawCall.h>

#include <glad/glad.h>
#include <assert.h>

static enum DrawMode {
	NONE,
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

	COUNT
};

bool DrawCmd(DrawMode drawmode, lgl::Primitive mode, lgl::Type type, lgl::Format format, int first, int start, int end, int count, int basevertex, int baseinstance, int instancecount, int width, int height, void* indices, void* indirect, void* pixels) {
	switch (drawmode) {
		case NONE:
			glDrawArrays(lgl::GetMap(mode), first, count);
			break;
		case INDIRECT:
			glDrawArraysIndirect(lgl::GetMap(mode), indirect);
			break;
		case INSTANCED:
			glDrawArraysInstanced(lgl::GetMap(mode), first, count, instancecount);
			break;
		case INSTANCED_BASEINSTANCE:
			glDrawArraysInstancedBaseInstance(lgl::GetMap(mode), first, count, instancecount, baseinstance);
			break;
			
		case INDEXED:
			glDrawElements(lgl::GetMap(mode), count, lgl::GetMap(type), indices);
			break;
		case INDEXED_INDIRECT:
			glDrawElementsIndirect(lgl::GetMap(mode), lgl::GetMap(type), indirect);
			break;
		case INDEXED_INSTANCED:
			glDrawElementsInstanced(lgl::GetMap(mode), count, lgl::GetMap(type), indices, instancecount);
			break;
		case INDEXED_BASEVERTEX:
			glDrawElementsBaseVertex(lgl::GetMap(mode), count, lgl::GetMap(type), indices, basevertex);
			break;
		case INDEXED_INSTANCED_BASEINSTANCE:
			glDrawElementsInstancedBaseVertex(lgl::GetMap(mode), count, lgl::GetMap(type), indices, instancecount, basevertex);
			break;
		case INDEXED_INSTANCED_BASEVERTEX:
			glDrawElementsInstancedBaseVertex(lgl::GetMap(mode), count,  lgl::GetMap(type), indices, instancecount, basevertex);
			break;
		case INDEXED_INSTANCED_BASEVERTEX_BASEINSTANCE:
			glDrawElementsInstancedBaseVertexBaseInstance(lgl::GetMap(mode), count, lgl::GetMap(type), indices, instancecount, basevertex, baseinstance);
			break;
		
		case RANGE_INDEXED:
			glDrawRangeElements(lgl::GetMap(mode), start, end, count, lgl::GetMap(type), indices);
			break;
		case RANGE_INDEXED_BASEVERTEX:
			glDrawRangeElementsBaseVertex(lgl::GetMap(mode), start, end, count, lgl::GetMap(type), indices, basevertex);
			break;

		case PIXELS:
			glDrawPixels(width, height, lgl::GetMap(format), lgl::GetMap(type), pixels);
			break;

		default:
			return false;
	}

	return true;
}

bool lgl::DrawIndexed(Primitive mode, int count, Type type, void* indices) {
	return DrawCmd(INDEXED, mode, type, (Format)0, 0, 0, 0, count, 0, 0, 0, 0, 0, indices, nullptr, nullptr);
}

bool lgl::Draw(Primitive mode, int first, int count) {
	return DrawCmd(NONE, mode, (Type)0, (Format)0, first, 0, 0, count, 0, 0, 0, 0, 0, nullptr, nullptr, nullptr);
}