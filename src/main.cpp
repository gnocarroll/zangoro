#include <iostream>

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

#include "Events.h"
#include "Window.h"

static struct AppState {
	Window window;
};

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
	*appstate = new AppState;

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	if (!event) {
		std::cerr << "event null\n";
		return SDL_APP_CONTINUE;
	}

	return handleEvent(event);
}

SDL_AppResult SDL_AppIterate(void* appstate) {
	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
	if (appstate) delete ((AppState*)appstate);
}