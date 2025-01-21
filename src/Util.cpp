#include "Util.h"

#include <algorithm>

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

void buf2DCpy(
	u8* dest,
	int destX, int destY, int destW, int destH,
	const u8* src,
	int srcW, int srcH) {

	int xStop = MIN(destW - destX, srcW);
	int yStop = MIN(destH - destY, srcH);

	for (int yRel = MAX(0, -destY); yRel < yStop; yRel++) {
		for (int xRel = MAX(0, -destX); xRel < xStop; xRel++) {
			dest[(destY + yRel) * destW + destX + xRel] =
				src[yRel * srcW + xRel];
		}
	}
}