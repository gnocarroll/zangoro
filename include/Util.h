#pragma once

#include <iostream>

template <auto func,typename... Args>
auto execAndCheck(Args... args) {
	auto ret = func(args...);

	if (ret) std::cerr << SDL_GetError();

	return ret;
}