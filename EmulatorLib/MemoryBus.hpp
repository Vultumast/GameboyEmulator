#pragma once

#include "Constants.hpp"

#include <vector>

class ROMInfo;
class MapperImpl;

class MemoryBus
{
private:
		uint8_t _ram[0x10000];
		ROMInfo* _rom = nullptr;
		MapperImpl* _mapper = nullptr;

		uint16_t translateAddress(uint16_t address);
public:
	MemoryBus(ROMInfo* rom);
	~MemoryBus();

	void Randomize();

	bool IsAddressMapped(const uint16_t& address);

	void Write(const uint16_t& address, const uint8_t& value);
	uint8_t Read(const uint16_t& address);
	/// <summary>
	/// Reads a word (16bit value) from a given address in Little Endianess
	/// </summary>
	/// <param name="address"></param>
	/// <returns></returns>
	uint16_t ReadWord(const uint16_t& address);

	void RequestInterrupt(Interrupt interrupt);
	Interrupt GetInterrupts();

	bool EchoRAMUsable = false;
};
