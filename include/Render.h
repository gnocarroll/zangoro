#pragma once

#include <SDL3/SDL.h>

#include "Util.h"
#include "Window.h"

class Render {
public:
	SDL_Renderer* ptr;

	Render(const Window& window) {
		ptr = execAndCheck<SDL_CreateRenderer>(window.ptr, nullptr);
	}
	Render(Render& other) = delete;
	Render(Render&& other) = default;

	~Render() {
		if (!ptr) return;

		SDL_DestroyRenderer(ptr);
	}
};