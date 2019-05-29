#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "globals.h"
#include "helpers.h"

static bool dort_in_square(float x, float y, float gx, float gy, float gw, float gh) {
	return (x >= gx && x <= gx + gw && y >= gy && y <= gy + gh);
}

static bool square_in_square(float x, float y, float w, float h, float gx, float gy, float gw, float gh) {
	return (
		dort_in_square(x, y, gx, gy, gw, gh) ||
		dort_in_square(x + w, y, gx, gy, gw, gh) ||
		dort_in_square(x, y + h, gx, gy, gw, gh) ||
		dort_in_square(x + w, y + h, gx, gy, gw, gh)
		);
}

static void init() {
	sf::Image mapImage ;
	mapImage.loadFromFile(MAP_FILE);
	mapImage.createMaskFromColor(Color(255, 255, 255));
	map = std::make_unique<Map>(mapImage, MAP_H, MAP_W);
	font = std::make_unique<sf::Font>();
	font->loadFromFile(FONT_FILE);
}
#endif
