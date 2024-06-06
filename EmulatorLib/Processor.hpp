#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <functional>

#include "Constants.hpp"

enum class Interrupt : uint8_t
{
	VBlank = 0b00000001,
	LCD = 0b00000010,
	Timer = 0b00000100,
	Joypad = 0b00001000,
};

class MemoryBus;

class Processor
{
public:
	Processor(MemoryBus* memoryBus);

	bool ime = false; // This should be private but it's never gonna get accessed outside the CPU anyway (hopefully)

	// "Event" functions
	void Reset();
	void PulseClock();
	void Interrupt(Interrupt interrupt);

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

	bool GetFlag(FLAGS flag) const;
	void SetFlag(FLAGS flag, bool value);

	uint16_t GetSourceValue(Register source, bool direct = true);
	uint16_t GetSourceValue(uint16_t source, bool direct = true);

	void SetDestinationValue(Register destination, uint16_t source, bool direct = true);
	void SetDestinationValue(uint16_t destination, uint16_t source, bool direct = true);

	uint16_t GetOperand(OperandType operand);

	uint8_t read(uint16_t addr);
	void write(uint16_t addr, uint8_t value);

	/// <summary>
	/// Pushes a value onto the stack and moves it back
	/// </summary>
	/// <param name="value"></param>
	void Push(uint16_t value);

	/// <summary>
	/// Stops current execution, pushing program counter to the stack and then jumping execution to the given address
	/// </summary>
	/// <param name="address"></param>
	void ResetVector(uint16_t address);
private:
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

	MemoryBus* _memoryBus = nullptr;

	uint8_t _byteLength = 1;
	uint8_t _remainingCycles = 4;
	uint8_t _cycleCount = 0;

	uint8_t fetch();
};

extern std::function<void(Processor&, OperandType, std::uint16_t, std::uint16_t) > Instructions[256];