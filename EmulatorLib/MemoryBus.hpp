#pragma once

#include "Constants.hpp"

#include <vector>

class MemoryBus
{
private:
		uint8_t _ram[0x10000];
public:
	void Randomize();

	bool IsAddressMapped(const uint16_t& address);

	void Write(const uint16_t& address, const uint8_t& value);
	uint8_t Read(const uint16_t& address);

	void WriteROM(const std::vector<uint8_t>& data);
};
