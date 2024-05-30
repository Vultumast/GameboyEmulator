#pragma once

#include "Constants.hpp"


class MemoryBus
{
private:
		std::uint8_t _ram[0x10000];
public:
	bool IsAddressMapped(const std::uint16_t& address);

	void Write(const std::uint16_t& address, const std::uint8_t& value);
	std::uint8_t Read(const std::uint16_t& address);
};
