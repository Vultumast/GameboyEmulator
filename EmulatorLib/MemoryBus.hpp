#pragma once

#include "Constants.hpp"

#include <vector>

enum class Interrupt : uint8_t
{
	None  = 0b00000000,
	VBlank = 0b00000001,
	LCD = 0b00000010,
	Timer = 0b00000100,
	Joypad = 0b00001000,
};

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

	void RequestInterrupt(Interrupt interrupt);
	Interrupt GetInterrupts();

};
