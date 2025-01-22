#pragma once

#include "MyIntDef.h"

#define CHUNK_WIDTH (32)

namespace Tilemap {
	enum class Direction : u16 {
		North = 0,
		East  = 1,
		South = 2,
		West  = 3
	};

	struct Tile {
		u16 id = 0;
		u16 r : 4 = 3;
		u16 g : 4 = 3;
		u16 b : 4 = 3;
		u16 rotation : 2 = 0;
		u16 isFlipped : 1 = 0;
	};

	struct Chunk {
		Tile front[CHUNK_WIDTH][CHUNK_WIDTH];
		Tile back[CHUNK_WIDTH][CHUNK_WIDTH];
	};

	struct ChunkInfo {
		Chunk* diskChunk = nullptr;
	};
}