#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <functional>

#include "Constants.hpp"

#include "InstructionArguments.hpp"
#include "OpCodeInfo.hpp";

enum Registers8Bit : uint8_t
{
	B,
	C,
	D,
	E,
	H,
	L,
	HL_Indirect,
	A
};

enum Registers16BitA : uint8_t
{
	BC,
	DE,
	HL,
	SP
};
enum Registers16BitB : uint8_t
{
	BC,
	DE,
	HL,
	AF
};
enum Conditionals : uint8_t
{
	NZ,
	Z,
	NC,
	C
};
enum ArithmeticLogicOperations : uint8_t
{
	ADD_A,
	ADC_A,
	SUB,
	SBC_A,
	AND,
	XOR,
	OR,
	CP
};
enum RotationShiftOperations : uint8_t
{
	RLC,
	RRC,
	RL,
	RR,
	SLA,
	SRA,
	SWAP,
	SRL
};


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

	OpCode _previousOpCode = OpCode::NOP;

	/// <summary>
	/// Fetches a uint8 from the address of the program counter and increments it by 1 (or resets if it's overflowing)
	/// </summary>
	/// <returns></returns>
	uint8_t fetch();

	/// <summary>
	/// Fetches a uint16 from the address of the program counter and increments it by 2 (or resets if it's overflowing)
	/// </summary>
	/// <returns></returns>
	uint16_t fetchWord();

	/// <summary>
	/// Services and performs underlying interrupts
	/// </summary>
	void serviceInterrupt(Interrupt interrupt);




	void decodeOpcode();

	void decodeOpCodeGroup0(uint8_t opcode);
	void decodeOpCodeGroup1(uint8_t opcode);
	void decodeOpCodeGroup2(uint8_t opcode);
	void decodeOpCodeGroup3(uint8_t opcode);


	void decodeOpCodeSubgroup00(uint8_t opcode);
	void decodeOpCodeSubgroup01(uint8_t opcode);
	void decodeOpCodeSubgroup02(uint8_t opcode);
	void decodeOpCodeSubgroup03(uint8_t opcode);
	void decodeOpCodeSubgroup04(uint8_t opcode);
	void decodeOpCodeSubgroup05(uint8_t opcode);
	void decodeOpCodeSubgroup06(uint8_t opcode);
	void decodeOpCodeSubgroup07(uint8_t opcode);

	void decodeOpCodeSubgroup30(uint8_t opcode);
	void decodeOpCodeSubgroup31(uint8_t opcode);
	void decodeOpCodeSubgroup32(uint8_t opcode);
	void decodeOpCodeSubgroup33(uint8_t opcode);
	void decodeOpCodeSubgroup34(uint8_t opcode);
	void decodeOpCodeSubgroup35(uint8_t opcode);
	void decodeOpCodeSubgroup36(uint8_t opcode);
	void decodeOpCodeSubgroup37(uint8_t opcode);
public:
	Processor(MemoryBus* memoryBus);

	bool InterruptMasterEnable = false;

	/// <summary>
	/// Is the CPU's execution be halted until an interrupt is requested?
	/// <para>Interrupts are only serviced if <c>InterruptMasterEnable</c> is enabled otherwise execution just resumes from where it was halted.</para>
	/// </summary>
	bool Halted = false;

	/// <summary>
	/// Is the CPU's execution halted?
	/// </summary>
	bool Stopped = false;

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


	void SetRegister8Bit(Registers8Bit destination, uint8_t value);
	uint8_t GetRegister8Bit(Registers8Bit source) const;
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