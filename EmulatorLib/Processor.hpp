#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <functional>

#include "Constants.hpp"

#include "InstructionArguments.hpp"
#include "OpCodeInfo.hpp";


class MemoryBus;

class Processor
{
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

	/// <summary>
	/// Fetches a byte from the address of the program counter and increments it by 1 (or resets if it's overflowing)
	/// </summary>
	/// <returns></returns>
	uint8_t fetch();

	/// <summary>
	/// Services and performs underlying interrupts
	/// </summary>
	void serviceInterrupt(Interrupt interrupt);

public:
	Processor(MemoryBus* memoryBus);

	bool InterruptMasterEnable = false;

	/// <summary>
	/// Should the CPUs execution be halted until an interrupt is requested?
	/// <para>Interrupts are only serviced if <c>InterruptMasterEnable</c> is enabled otherwise execution just resumes from where it was halted.</para>
	/// </summary>
	bool Halted = false;

	/// <summary>
	/// Resets the CPU, resetting all registers to what they were at boot
	/// </summary>
	void Reset();

	void PulseClock();

	void ConsumeInstruction();

	/// <summary>
	/// Has the current underlying instruction completed it's clock cycles?
	/// </summary>
	/// <returns></returns>
	bool IsInstructionCompleted() const { return _remainingCycles == 0; }

	uint8_t GetRemainingCycles() const { return _remainingCycles; }

	void SetRegister(Register destination, uint16_t value);
	uint16_t GetRegister(Register source) const;

	enum FLAGS
	{
		/// <summary>
		/// The "Carry" flag
		/// </summary>
		C = (1 << 4),
		/// <summary>
		/// The "Half-Carry" flag
		/// </summary>
		H = (1 << 5),
		/// <summary>
		/// The "Negative" or "Subtraction" flag
		/// </summary>
		N = (1 << 6),
		/// <summary>
		/// The "Zero" flag
		/// </summary>
		Z = (1 << 7),
	};

	bool GetFlag(FLAGS flag) const;
	void SetFlag(FLAGS flag, bool value);

	uint16_t GetSourceValue(Register source, bool direct = true);
	uint16_t GetSourceValue(uint16_t source, bool direct = true);

	void SetDestinationValue(Register destination, uint16_t source, bool direct = true);
	void SetDestinationValue(uint16_t destination, uint16_t source, bool direct = true);

	uint16_t GetOperand(OperandType operand);

	/// <summary>
	/// Pushes a value onto the stack and decrements the stack pointer by 2
	/// </summary>
	/// <param name="value"></param>
	void StackPush(uint16_t value);

	/// <summary>
	/// Pops a value off of the stack and increments the stack pointer by 2
	/// </summary>
	/// <returns></returns>
	uint16_t StackPop();

	/// <summary>
	/// Stops current execution, pushing program counter to the stack and then jumping execution to the given address
	/// </summary>
	/// <param name="address"></param>
	void ResetVector(uint16_t address);

	/// <summary>
	/// The underlying memorybus associated with the processor
	/// </summary>
	/// <returns></returns>
	MemoryBus* GetMemoryBus() { return _memoryBus;  }
};

extern std::function<void(InstructionArguments&) > Instructions[256];
extern std::function<void(InstructionArguments&) > InstructionsCB[256];