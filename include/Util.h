#pragma once

#include <iostream>

#include <SDL3/SDL.h>

#include "MyIntDef.h"
#include "Math/Rect.h"

template <auto func,typename... Args>
auto execAndCheck(Args... args) {
	auto ret = func(args...);

	if (ret) std::cerr << SDL_GetError();

	return ret;
}

// copy entirety (or whatever can fit) of src into dest
// at provided coordinates destX, destY

void buf2DCpy(
	u8* dest,
	int destX, int destY, int destW, int destH,
	const u8* src,
	int srcW, int srcH);
