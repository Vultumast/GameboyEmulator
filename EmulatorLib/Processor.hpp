#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "Constants.hpp"

#include "OpCodeInfo.hpp"


class Processor
{

public:
	Processor();

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
	void reset();
	void interrupt();
	void nmi();
	void clock();

	bool isInstructionCompleted();

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
	uint8_t remaining_cycles = 0;
	uint16_t cycle_count = 0;

	uint8_t read(uint16_t addr);
	void write(uint16_t addr, uint8_t value);

	uint8_t fetch();

	struct INSTRUCTION
	{
		std::string name;
		uint8_t (*operation)(void) = nullptr;
		uint8_t (*addr_mode)(void) = nullptr;
		uint8_t cycles = 0;
	};

private:
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

private:
	// Operations (TODO)

	// The list of operations I've come up with is this, may need to be tweaked
	/*
	NOP
	STOP
	HALT
	PREFIX
	EI
	DI
	JR
	JP
	RET
	RETI
	CALL
	RST
	LD8
	LDH
	LD16
	PUSH
	POP
	INC
	DEC
	ADD8
	ADC
	SUB
	SBC
	AND
	XOR
	OR
	CP
	DAA
	CPL
	SCF
	CCF
	ADD16
	RLCA
	RRCA
	RLA
	RRA
	RLC
	RRC
	RL
	RR
	SLA
	SRA
	SWAP
	SRL
	BIT
	RES
	SET

	XXX // this is for invalid opcodes so they can freeze, be ignored, be logged, w/e
	*/

};