#pragma once

#include "Constants.hpp"

struct Tile
{
private:
	uint8_t _data[16];
public:

	uint8_t GetPixel(uint8_t x, uint8_t y);
};