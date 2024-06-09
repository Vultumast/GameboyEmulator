#pragma once

#include "MapperImpl.hpp"

class MBC1Mapper : public MapperImpl
{
private:

public:
	MBC1Mapper(ROMInfo* rom) : MapperImpl(rom)
	{

	}

	void Write(uint16_t address, uint8_t value);
	uint8_t Read(uint16_t address);

	void Reset();
};