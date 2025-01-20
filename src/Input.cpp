#include "Input.h"

#include <iostream>

#include "MyIntDef.h"

void Input::checkEvent(const SDL_Event& event) {
	bool relevant = true;

	switch (event.type) {
	case SDL_EVENT_KEY_DOWN:
	case SDL_EVENT_KEY_UP:
		if (event.key.repeat) break;

		isScanPressed[event.key.scancode] = event.key.down;
		scanPresses[event.key.scancode]++;
		break;
	case SDL_EVENT_MOUSE_MOTION:
		mouse.x = event.motion.x;
		mouse.y = event.motion.y;
		mouse.xrel += event.motion.xrel;
		mouse.yrel += event.motion.yrel;
		break;
	case SDL_EVENT_MOUSE_WHEEL: {
		bool flipped = (event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED);
		mouseWheel.xrel += event.wheel.x;
		mouseWheel.yrel += event.wheel.y;
		mouse.x = event.wheel.mouse_x;
		mouse.y = event.wheel.mouse_y;
		break;
	}
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
	case SDL_EVENT_MOUSE_BUTTON_UP: {
		u8 idx = event.button.button;

		if (idx >= MOUSE_BUTTON_COUNT) {
			std::cerr << "Mouse button index too large\n";
			break;
		}

		isMousePressed[idx] = event.button.down;
		mousePresses[idx] += event.button.clicks;

		mouse.x = event.button.x;
		mouse.y = event.button.y;

		break;
	}
	default:
		relevant = false;
		break;
	}

	if (relevant) gotEvent = true;
}