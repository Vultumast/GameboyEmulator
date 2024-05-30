#pragma once

#include <cstdint>

#include "Constants.hpp"


enum ProcessorRegisters
{
	AF,
	BC,
	DE,
	HL,
	SP,
	PC,
};

enum ProcessorFlags
{
	CarryFlag = 4,
	HalfCarryFlag,
	SubtractionCarryFlag,
	ZeroFlag,
};
class Processor
{
private:
	std::uint16_t _registerAF = 0x0000;
	std::uint16_t _registerBC = 0x0000;
	std::uint16_t _registerDE = 0x0000;
	std::uint16_t _registerHL = 0x0000;
	std::uint16_t _registerSP = 0x0000;
	std::uint16_t _registerPC = 0x0000;

public:
	void Write(ProcessorRegisters reg, std::uint16_t value);
	void WriteHi(ProcessorRegisters reg, std::uint8_t value);
	void WriteLo(ProcessorRegisters reg, std::uint8_t value);

	std::uint16_t Read(ProcessorRegisters reg);
	std::uint8_t ReadHi(ProcessorRegisters reg);
	std::uint8_t ReadLo(ProcessorRegisters reg);
};