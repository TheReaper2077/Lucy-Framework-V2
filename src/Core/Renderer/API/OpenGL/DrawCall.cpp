#include <GraphicsAPI/DrawCall.h>

#include <glad/glad.h>
#include <assert.h>

int& lgl::DrawIndexed(Primitive mode, int count, Type type, void* indices) {
	return DrawCmd(INDEXED, mode, type, (Format)0, 0, 0, 0, count, 0, 0, 0, 0, 0, indices, nullptr, nullptr);
}

int& lgl::Draw(Primitive mode, int first, int count) {
	return DrawCmd(NONE, mode, (Type)0, (Format)0, first, 0, 0, count, 0, 0, 0, 0, 0, nullptr, nullptr, nullptr);
}

int& lgl::DrawCmd(DrawMode drawmode, Primitive mode, Type type, Format format, int first, int start, int end, int count, int basevertex, int baseinstance, int instancecount, int width, int height, void* indices, void* indirect, void* pixels) {
	static int drawcount;
	
	switch (drawmode) {
		case NONE:
			glDrawArrays(GetMap(mode), first, count);
			break;
		case INDIRECT:
			glDrawArraysIndirect(GetMap(mode), indirect);
			break;
		case INSTANCED:
			glDrawArraysInstanced(GetMap(mode), first, count, instancecount);
			break;
		case INSTANCED_BASEINSTANCE:
			glDrawArraysInstancedBaseInstance(GetMap(mode), first, count, instancecount, baseinstance);
			break;
			
		case INDEXED:
			glDrawElements(GetMap(mode), count, GetTypeMap(type), indices);
			break;
		case INDEXED_INDIRECT:
			glDrawElementsIndirect(GetMap(mode), GetTypeMap(type), indirect);
			break;
		case INDEXED_INSTANCED:
			glDrawElementsInstanced(GetMap(mode), count, GetTypeMap(type), indices, instancecount);
			break;
		case INDEXED_BASEVERTEX:
			glDrawElementsBaseVertex(GetMap(mode), count, GetTypeMap(type), indices, basevertex);
			break;
		case INDEXED_INSTANCED_BASEINSTANCE:
			glDrawElementsInstancedBaseVertex(GetMap(mode), count, GetTypeMap(type), indices, instancecount, basevertex);
			break;
		case INDEXED_INSTANCED_BASEVERTEX:
			glDrawElementsInstancedBaseVertex(GetMap(mode), count,  GetTypeMap(type), indices, instancecount, basevertex);
			break;
		case INDEXED_INSTANCED_BASEVERTEX_BASEINSTANCE:
			glDrawElementsInstancedBaseVertexBaseInstance(GetMap(mode), count, GetTypeMap(type), indices, instancecount, basevertex, baseinstance);
			break;
		
		case RANGE_INDEXED:
			glDrawRangeElements(GetMap(mode), start, end, count, GetTypeMap(type), indices);
			break;
		case RANGE_INDEXED_BASEVERTEX:
			glDrawRangeElementsBaseVertex(GetMap(mode), start, end, count, GetTypeMap(type), indices, basevertex);
			break;

		case PIXELS:
			glDrawPixels(width, height, GetMap(format), GetTypeMap(type), pixels);
			break;
		
		default:
			return drawcount;
	}

	drawcount++;

	return drawcount;
}