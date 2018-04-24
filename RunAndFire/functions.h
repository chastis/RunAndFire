#ifndef FUNCTIONS_H
#define FUNCTIONS_H

bool dort_in_square(float x, float y, float gx, float gy, float gw, float gh) {
	return (x >= gx && x <= gx + gw && y >= gy && y <= gy + gh);
}

bool square_in_square(float x, float y, float w, float h, float gx, float gy, float gw, float gh) {
	return (
		dort_in_square(x, y, gx, gy, gw, gh) ||
		dort_in_square(x + w, y, gx, gy, gw, gh) ||
		dort_in_square(x, y + h, gx, gy, gw, gh) ||
		dort_in_square(x + w, y + h, gx, gy, gw, gh)
		);
}
#endif
