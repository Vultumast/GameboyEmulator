#include "Tile.hpp"

uint8_t Tile::GetPixel(uint8_t x, uint8_t y)
{
	// Vultu: IDK if this is the best practice but eh
	if (x >= 8 || y >= 8)
		return 0xFF; 

	uint8_t bit = (7 - x);

	// Zipper two bytes together
	return ((_data[(y * 2) + 1] & (0b1 << (7 - x))) != 0 ? 0b10 : 0b00) | ((_data[y * 2] & (0b1 << (7 - x))) != 0 ? 0b01 : 0b00);
}
