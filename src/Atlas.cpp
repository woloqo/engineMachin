#include "../include/Atlas.h"

UVRect tileToUvRect(int tileId){
	int col = tileId % TILES_PER_ROW;
	int row = tileId / TILES_PER_ROW;

	float uMin = col * TILE_UV_SIZE;
	float uMax = uMin + TILE_UV_SIZE;
	float vMax = 1.0 - row * TILE_UV_SIZE;
	float vMin = vMax - TILE_UV_SIZE;

	float epsilon = 0.01 / ATLAS_SIZE;
	uMin += epsilon;
	uMax -= epsilon;
	vMin += epsilon;
	vMax -= epsilon;

	return UVRect(uMin, vMin, uMax, vMax);
}

glm::vec2 localToAtlasUV(glm::vec2 localUV, const UVRect& rect) {
    return rect.min + localUV * (rect.max - rect.min);
}