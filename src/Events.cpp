#include <iostream>

#include <SDL3/SDL.h>

#include "Events.h"
#include "MyIntDef.h"

template <>
static inline SDL_AppResult Events::handleSpecific<SDL_EVENT_WINDOW_DESTROYED>(SDL_Event* event) {
	return SDL_APP_SUCCESS;
}

template <>
static inline SDL_AppResult Events::handleSpecific<SDL_EVENT_WINDOW_CLOSE_REQUESTED>(SDL_Event* event) {
	return SDL_APP_SUCCESS;
}

#define EVENT_CASE(x, event) case x: return handleSpecific<x>(event)

SDL_AppResult Events::handleEvent(SDL_Event* event) {
	if (!event) {
		std::cerr << "handleEvent event null\n";
		return SDL_APP_CONTINUE;
	}

	switch (event->type) {
	EVENT_CASE(SDL_EVENT_WINDOW_DESTROYED, event);
	EVENT_CASE(SDL_EVENT_WINDOW_CLOSE_REQUESTED, event);
	default:
		break;
	}

	// have input look at event to see if it should update its internal state

	input.checkEvent(*event);

	return SDL_APP_CONTINUE;
}