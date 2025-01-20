#pragma once

#include <SDL3/SDL.h>

// may wait to implement until I am sure vcpkg works with this and sdl3

namespace Image {
	class Texture {
	public:
		SDL_Texture* ptr;

		Texture(const char* filepath) {
			ptr = nullptr;
		};
		Texture(Texture& other) = delete;
		Texture(Texture&& other) = default;

		~Texture() {
			if (!ptr) return;

			SDL_DestroyTexture(ptr);
			ptr = nullptr;
		}
	};
}