#include "RomInfo.hpp"

#include "MBC1.hpp"

#include <iostream>

void MBC1Mapper::Write(uint16_t address, uint8_t value)
{
	ROMInfo* rom = GetROMInfo();

	if (address <= 0x1FFF)
		_ramEnabled = (value & 0xF) == 0xA;
	else if (address <= 0x3FFF)
	{
		std::cout << "ROM BANKED SWITCHED" << std::endl;

		_romBank = value & 0b00011111;

		if (_romBank == 0)
			_romBank = 1;
	}
	else if (rom->HasRAM())
	{

	}
}

uint8_t MBC1Mapper::Read(uint16_t address)
{
	ROMInfo* rom = GetROMInfo();

	if (address <= 0x7FFF && address > 0x3FFFF)
		return rom->Read(0x4000 * _romBank);

	if (address <= 0x3FFF)
		return rom->Read(address);

}

void MBC1Mapper::Reset()
{
	_romBank = 1;
	_ramEnabled = false;
	_rumbleEnabled = false;
}