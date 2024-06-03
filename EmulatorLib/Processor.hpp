#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <functional>

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

	bool IsInstructionCompleted() const { return _remainingCycles == 0; }

	void SetRegister(Register destination, uint16_t value);
	uint16_t GetRegister(Register source) const;

	enum FLAGS
	{
		C = (1 << 4),
		H = (1 << 5),
		N = (1 << 6),
		Z = (1 << 7),
	};

	uint8_t GetFlag(FLAGS flag) const;
	void SetFlag(FLAGS flag, bool value);

	uint16_t GetSourceValue(Register source, bool direct = true);
	uint16_t GetSourceValue(uint16_t source, bool direct = true);

	void SetDestinationValue(Register destination, uint16_t source, bool direct = true);
	void SetDestinationValue(uint16_t destination, uint16_t source, bool direct = true);


private:

	uint8_t read(uint16_t addr);
	void write(uint16_t addr, uint8_t value);
	
	MemoryBus* _memoryBus = nullptr;

	uint8_t _byteLength = 1;
	uint8_t _remainingCycles = 4;
	uint8_t _cycleCount = 0;

	uint8_t fetch();
};

extern std::function<void(Processor&, std::uint16_t) > Instructions[256];