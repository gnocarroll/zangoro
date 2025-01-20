#include <iostream>

#include <SDL3/SDL.h>

#include "Events.h"
#include "MyIntDef.h"

template <u32 eventType>
static inline SDL_AppResult handleSpecific(SDL_Event* event) {
	std::cerr << "No handler implemented\n";

	return SDL_APP_CONTINUE;
}

template <>
static inline SDL_AppResult handleSpecific<SDL_EVENT_WINDOW_DESTROYED>(SDL_Event* event) {
	return SDL_APP_SUCCESS;
}

template <>
static inline SDL_AppResult handleSpecific<SDL_EVENT_WINDOW_CLOSE_REQUESTED>(SDL_Event* event) {
	return SDL_APP_SUCCESS;
}

#define EVENT_CASE(x, event) case x: return handleSpecific<x>(event)

SDL_AppResult handleEvent(SDL_Event* event) {
	switch (event->type) {
	EVENT_CASE(SDL_EVENT_WINDOW_DESTROYED, event);
	EVENT_CASE(SDL_EVENT_WINDOW_CLOSE_REQUESTED, event);
	default:
		break;
	}

	return SDL_APP_CONTINUE;
}