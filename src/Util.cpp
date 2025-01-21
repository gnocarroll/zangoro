#include "Util.h"

#include <algorithm>

void buf2DCpy(
	u8* dest,
	int destX, int destY, int destW, int destH,
	const u8* src,
	int srcW, int srcH) {

	int xRel = 0;
	int yRel = 0;

	if (destX < 0) xRel -= destX;
	if (destY < 0) yRel -= destY;

	int xStop = std::min(destW - destX, srcW);
	int yStop = std::min(destH - destY, srcH);

	for (; yRel < yStop; yRel++) {
		for (; xRel < xStop; xRel++) {
			dest[(destY + yRel) * destW + destX + xRel] =
				src[yRel * srcW + xRel];
		}
	}
}