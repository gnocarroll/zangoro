#pragma once

#include <iostream>

#include <SDL3/SDL.h>

#include "Input.h"
#include "MyIntDef.h"

class Events {
private:
	Input& input;

	template <u32 eventType>
	static inline SDL_AppResult handleSpecific(SDL_Event* event) {
		std::cerr << "No handler implemented or in wrong translation unit\n";

		return SDL_APP_CONTINUE;
	}
public:
	Events(Input& _input) : input(_input) {};

	SDL_AppResult handleEvent(SDL_Event* event);
};