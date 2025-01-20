#pragma once

#include <array>
#include <bitset>

#include <SDL3/SDL.h>

// max mouse buttons

#define MOUSE_BUTTON_COUNT (64)

class Input {
private:
	bool gotEvent = false;

	std::bitset<SDL_SCANCODE_COUNT> isScanPressed{};
	std::array<int, SDL_SCANCODE_COUNT> scanPresses{};
	
	std::bitset<MOUSE_BUTTON_COUNT> isMousePressed{};
	std::array<int, MOUSE_BUTTON_COUNT> mousePresses{};

	struct {
		float x    = 0.0f;
		float y    = 0.0f;
		float xrel = 0.0f;
		float yrel = 0.0f;
	} mouse;

	struct {
		float xrel = 0.0f;
		float yrel = 0.0f;
	} mouseWheel;
public:

	// check event to see if internal state should be updated

	void checkEvent(const SDL_Event& event);

	// member functions for querying input

	// get bool indicating if relevant event arrived to class since last time checked

	bool gotRelevantEvent() {
		bool ret = gotEvent;
		gotEvent = false;
		return ret;
	};

	// below relate to specific keys, mouse inputs, etc.

	bool getScan(SDL_Scancode scan) const;
	bool getKey(SDL_Keycode key) const;

	int getScanCount(SDL_Scancode scan) const { return scanPresses[scan]; };
	int getKeyCount(SDL_Keycode key) const {
		return scanPresses[SDL_GetScancodeFromKey(key, nullptr)];
	};

	float mouseX() const { return mouse.x; };
	float mouseY() const { return mouse.y; };
	float mouseXRel() const { return mouse.xrel; };
	float mouseYRel() const { return mouse.yrel; };

	bool getMouse(int idx) const;
	int getMouseCount(int idx) const { return mousePresses[idx]; };

	float mouseWheelXRel() const { return mouseWheel.xrel; };
	float mouseWheelYRel() const { return mouseWheel.yrel; };
};