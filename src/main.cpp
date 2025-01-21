#include <memory>

#include <SDL3/SDL.h>

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

#include "Events.h"
#include "Input.h"
#include "Render.h"
#include "UI/Font.h"
#include "Window.h"

using namespace UI;

struct AppState {
	// Besides window these are meant to be thought of kind of like
	// service (e.g. Angular)

	FontService font;
	Window window;
	Render render = Render(window);
	Input input;
	Events events = Events(input);
};

static std::unique_ptr<AppState> appState;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
	// SDL sets to NULL anyways but might as well

	*appstate = nullptr;

	SDL_InitSubSystem(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK |
		SDL_INIT_GAMEPAD | SDL_INIT_EVENTS);

	// will store appstate globally as this makes its disposal easy/clean

	appState.reset(new AppState);

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	return appState->events.handleEvent(event);
}

SDL_AppResult SDL_AppIterate(void* appstate) {
	if (appState->input.getKeyCount(SDLK_ESCAPE)) return SDL_APP_SUCCESS;

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {}