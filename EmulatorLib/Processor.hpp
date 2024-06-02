#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "Constants.hpp"

#include "OpCodeInfo.hpp"


class MemoryBus;

class Processor
{
public:
	Processor(MemoryBus* memoryBus);

	// Registers
	uint8_t a = 0x00;
	uint8_t b = 0x00;
	uint8_t c = 0x00;
	uint8_t d = 0x00;
	uint8_t e = 0x00;
	uint8_t f = 0x00;
	uint8_t h = 0x00;
	uint8_t l = 0x00;
	uint16_t sp = 0x0000;
	uint16_t pc = 0x0000;

	bool ime = false; // This should be private but it's never gonna get accessed outside the CPU anyway (hopefully)

	// "Event" functions
	void Reset();
	void PulseClock();
	void interrupt();
	void nmi();

	bool IsInstructionCompleted() { return _remainingCycles == 0; }

	void SetRegister(Register destination, uint16_t value);
	uint16_t GetRegister(Register destination);

	enum FLAGS
	{
		C = (1 << 4),
		H = (1 << 5),
		N = (1 << 6),
		Z = (1 << 7),
	};

private:
	uint8_t GetFlag(FLAGS flag);
	void SetFlag(FLAGS flag, bool value);

	// Internal values
	uint8_t fetched = 0x00;
	uint16_t addr = 0x0000;
	uint8_t opcode = 0x00;

	uint8_t read(uint16_t addr);
	void write(uint16_t addr, uint8_t value);


	struct INSTRUCTION
	{
		std::string name;
		uint8_t (*operation)(void) = nullptr;
		uint8_t (*addr_mode)(void) = nullptr;
		uint8_t cycles = 0;
	};

private:

	MemoryBus* _memoryBus = nullptr;

	uint8_t _byteLength = 1;
	uint8_t _remainingCycles = 4;
	uint8_t _cycleCount = 0;

	uint8_t fetch();

	void op_NOP();
	void op_LD(Register destination, Register source);
	void op_LD(uint16_t destination, Register source);
	void op_LD(Register destination, uint16_t source);


	// Addressing modes
	uint8_t ADDR_R8();
	uint8_t ADDR_R16();
	uint8_t ADDR_R16STK();
	uint8_t ADDR_R16MEM();
	uint8_t ADDR_COND();
	uint8_t ADDR_B3();
	uint8_t ADDR_TGT3();
	uint8_t ADDR_IMM8();
	uint8_t ADDR_IMM16();

};