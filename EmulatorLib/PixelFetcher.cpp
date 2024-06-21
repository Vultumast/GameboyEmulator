#include "MemoryBus.hpp"
#include "Video.hpp"

#include "PixelFetcher.hpp"
#include <bit>

void PixelFetcher::state_GetTile()
{
	uint32_t windowSize = 32 * 8;


	uint8_t viewportY = _mmu->Read(HardwareRegister::SCY);
	uint8_t viewportX = _mmu->Read(HardwareRegister::SCX);

	uint8_t windowY = _mmu->Read(HardwareRegister::WY);
	uint8_t windowX = _mmu->Read(HardwareRegister::WX) - 7;

	uint8_t scanline = _mmu->Read(HardwareRegister::LY);

	LCDControlRegister* lcdc = reinterpret_cast<LCDControlRegister*>(_mmu->Get(HardwareRegister::LCDC));

	uint16_t tilemapAddress = 0x9800;


	bool window = lcdc->WindowEnable && windowY <= scanline;

	_state = PixelFetcherState::ReadTileDataLow;
}

void state_ReadTileDataLow();
void state_ReadTileDataHigh();
void state_PushToFifo()
{

}
PixelFetcher::PixelFetcher(MemoryBus& mmu)
{
	_mmu = &mmu;
}
void PixelFetcher::Start(uint16_t addr, uint8_t tileLine, uint16_t x, uint16_t y)
{
	_tileIndex = 0;
	_tileLine = tileLine;

	_drawX = x;
	_drawY = y;

	_state = PixelFetcherState::GetTile;
}
void PixelFetcher::Tick()
{
	static uint8_t ticker = 0;

	ticker++;

	if (ticker < 2)
		return;

	ticker = 0;


	switch (_state)
	{
	case PixelFetcherState::GetTile:
		state_GetTile();
		break;
	case PixelFetcherState::ReadTileDataLow:

		_state = PixelFetcherState::ReadTileDataHigh;
		break;
	case PixelFetcherState::ReadTileDataHigh:

		_state = PixelFetcherState::PushToFIFO;
		break;
	case PixelFetcherState::PushToFIFO:

		_state = PixelFetcherState::GetTile;
		break;
	}
}