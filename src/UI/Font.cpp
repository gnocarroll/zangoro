#include "UI/Font.h"

#include <algorithm>

#include <SDL3/SDL.h>

#include "Util.h"

namespace UI {
	Font FontService::getFont(const char* filepath, int idx) const {
		Font font;
		
		if (!filepath) {
			std::cerr << "filepath NULL\n";
		}
		else if (FT_New_Face(library, filepath, idx, &font.face)) {
			std::cerr << "Error occurred while creating face\n";
		}

		return font;
	}

	BitmapFont Font::renderFont(int h) const {
		BitmapFont bitmapFont;

		if (FT_Set_Pixel_Sizes(face, 0, h)) {
			std::cerr << "FT_Set_Pixel_Sizes failed\n";
			return bitmapFont;
		}

		// save handle to current glyph

		FT_GlyphSlot glyph = face->glyph;
		bitmapFont.w = 0;

		int yMax = INT_MIN;
		int yMin = INT_MAX;

		// dimensions of buffer for storing bitmap
		// also store info for characters

		for (int i = 33; i < BITMAP_CHAR_COUNT; i++) {
			if (FT_Load_Char(face, i, FT_LOAD_RENDER)) return bitmapFont;

			bitmapFont.info[i].x = bitmapFont.w;
			
			bitmapFont.info[i].bitmap_left = glyph->bitmap_left;
			bitmapFont.info[i].bitmap_top = glyph->bitmap_top;

			bitmapFont.info[i].w = glyph->bitmap.width;
			bitmapFont.info[i].h = glyph->bitmap.rows;

			bitmapFont.info[i].advancePx = glyph->advance.x >> 6;

			bitmapFont.w += bitmapFont.info[i].advancePx;

			yMax = std::max(yMax, (int) glyph->bitmap_top);
			yMin = std::min(yMin, (int) glyph->bitmap_top - (int) glyph->bitmap.rows);
		}

		// now allocate buffer for bitmap font and actually copy in rendered
		// characters

		bitmapFont.h = yMax - yMin;
		bitmapFont.buf = std::vector<u8>(bitmapFont.w * bitmapFont.h);

		bitmapFont.origin = yMax;

		for (int i = 33; i < BITMAP_CHAR_COUNT; i++) {
			if (FT_Load_Char(face, i, FT_LOAD_RENDER)) return bitmapFont;

			//auto window = SDL_CreateWindow(
			//	"letter",
			//	glyph->bitmap.width, glyph->bitmap.rows,
			//	0
			//);
			//auto render = SDL_CreateRenderer(window, nullptr);
			//SDL_RenderClear(render);

			//std::vector<u8> surfaceData(4 * glyph->bitmap.width * glyph->bitmap.rows);

			//for (int i = 0; i < surfaceData.size(); i++) {
			//	if (i % 4 == 0) {
			//		surfaceData[i] = glyph->bitmap.buffer[i / 4];
			//	}
			//	else surfaceData[i] = 255;
			//}

			//SDL_Surface* surface = SDL_CreateSurfaceFrom(
			//	glyph->bitmap.width, glyph->bitmap.rows,
			//	SDL_PIXELFORMAT_ABGR8888,
			//	surfaceData.data(),
			//	glyph->bitmap.width * 4
			//);
			//SDL_Texture* tex = SDL_CreateTextureFromSurface(
			//	render,
			//	surface
			//);

			//SDL_RenderTexture(render, tex, nullptr, nullptr);
			//SDL_RenderPresent(render);

			buf2DCpy(
				bitmapFont.buf.data(),

				bitmapFont.info[i].x + bitmapFont.info[i].bitmap_left,
				bitmapFont.origin - bitmapFont.info[i].bitmap_top,

				bitmapFont.w, bitmapFont.h,

				glyph->bitmap.buffer,

				bitmapFont.info[i].w, bitmapFont.info[i].h
			);
		}

		return bitmapFont;
	}
}