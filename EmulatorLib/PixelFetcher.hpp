#pragma once

#include "Constants.hpp"

enum class PixelFetcherState
{
	GetTile,
	ReadTileDataLow,
	ReadTileDataHigh,
	PushToFIFO
};


class MemoryBus;

struct FIFOPixel
{
public:
	DMGColor Color;

};
class PixelFetcher
{
private:
	PixelFetcherState _state = PixelFetcherState::GetTile;
	MemoryBus* _mmu = nullptr;

	uint8_t _tileIndex = 0;
	uint8_t _tileLine = 0;

	uint16_t _drawX = 0;
	uint16_t _drawY = 0;

	void state_GetTile();
	void state_ReadTileDataLow();
	void state_ReadTileDataHigh();
	void state_PushToFifo();
public:
	PixelFetcher(MemoryBus& mmu);

	void Start(uint16_t addr, uint8_t tileLine, uint16_t x, uint16_t y);
	void Tick();


	PixelFetcherState GetState() const { return _state; }
};