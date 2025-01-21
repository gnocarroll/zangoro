#pragma once

#include <array>
#include <iostream>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <SDL3/SDL.h>

#include "MyIntDef.h"

#define BITMAP_CHAR_COUNT (128)

namespace UI {
	class BitmapFont {
	public:
		struct charInfo {
			int x;

			int bitmap_left;
			int bitmap_top;

			int w;
			int h;

			int advancePx;
		};

		int requestH = 0;

		// offset from top to baseline of text

		int origin = 0;

		std::vector<u8> buf;
		
		int w = 0;
		int h = 0;

		std::array<charInfo, BITMAP_CHAR_COUNT> info{};



		BitmapFont() {}
		BitmapFont(BitmapFont& other) = delete;
		BitmapFont(BitmapFont&& other) = default;
	};

	class Font {
	public:
		FT_Face face = nullptr;
		
		Font() {}
		Font(Font& other) = delete;
		Font(Font&& other) = default;

		~Font() {
			if (face) FT_Done_Face(face);
		}

		// Render font with specified height (in pixels)
		// and get BitmapFont object containing information

		BitmapFont renderFont(int h) const;
	};

	class FontService {
	private:
		FT_Library library = nullptr;

	public:
		FontService() {
			if (FT_Init_FreeType(&library)) {
				std::cerr << "problem during FT init";
			}
		};
		FontService(FontService& other) = delete;
		FontService(FontService&& other) = default;

		~FontService() {
			if (library) FT_Done_FreeType(library);
		}

		Font getFont(const char *filepath, int idx = 0) const;
	};
};