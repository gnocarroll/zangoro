#pragma once

#include <SDL3/SDL.h>

#include "Constants.h"
#include "Util.h"

struct Window {
	SDL_Window* ptr;

	Window() {
		ptr = execAndCheck<SDL_CreateWindow>(
			GAME_NAME,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			WINDOW_FLAGS
		);
	}
	Window(Window& other) = delete;
	Window(Window&& other) = default;
	
	~Window() {
		if (ptr) SDL_DestroyWindow(ptr);

		ptr = nullptr;
	}
};