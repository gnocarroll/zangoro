#pragma once

#include <SDL3/SDL.h>

#include "MyIntDef.h"
#include "Util.h"

namespace Image {
	class Texture {
	public:
		SDL_Texture* ptr = nullptr;

		Texture(const char* filepath) {};
		Texture(SDL_Renderer* render, SDL_Surface* surface) {
			ptr = execAndCheck<SDL_CreateTextureFromSurface>(render, surface);
		}
		Texture(Texture& other) = delete;
		Texture(Texture&& other) = default;

		~Texture() {
			if (!ptr) return;

			SDL_DestroyTexture(ptr);
			ptr = nullptr;
		}
	};
}