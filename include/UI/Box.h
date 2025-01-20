#pragma once

#include <string>

#include "Image/Texture.h"
#include "Math/Vec.h"

#define U8_0 ((u8) 0)
#define OPAQUE_ALPHA ((u8) 255)

namespace UI {
	class Box {
	private:
		constexpr static Color blankColor = Color(U8_0, U8_0, U8_0, U8_0);

		bool isRendered = false;
		bool lineBreakAfter = false;
		
		float padding = 0.0f;
		float fontpx = 10.0f;

		struct {
			float x = 0.0f;
			float y = 0.0f;
			float w = 0.0f;
			float h = 0.0f;
		} pos;

		struct {
			Color padding = blankColor;
			Color text = Color(U8_0, U8_0, U8_0, OPAQUE_ALPHA);
			Color background = blankColor;
		} color;

		struct {
			Color mult;
		} transform;

		struct {
			const std::string* text = nullptr;
			const Image::Texture* img = nullptr;
		} contents;

	public:
		// Render box

		bool Render() {

		}
	};
}