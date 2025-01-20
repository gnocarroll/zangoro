#pragma once

#include <SDL3/SDL.h>

// can load images directly into textures so I do not actually need this class
// may not implement it

namespace Image {
	class Surface {
	public:
		SDL_Surface* ptr;

		Surface(const char* filepath) {
			ptr = nullptr;
		}
		Surface(Surface& other) = delete;
		Surface(Surface&& other) = default;

		~Surface() {
			if (!ptr) return;

			SDL_DestroySurface(ptr);
			ptr = nullptr;
		}
	};
}