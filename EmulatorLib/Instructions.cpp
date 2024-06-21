#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "MemoryBus.hpp"
#include "InstructionArguments.hpp"

#include "Processor.hpp"

void op_NOP(InstructionArguments&);
void op_STOP(InstructionArguments&);
void op_HALT(InstructionArguments&);
void op_EI(InstructionArguments&);
void op_DI(InstructionArguments&);
void op_LD(InstructionArguments&);
void op_PUSH(InstructionArguments&);
void op_POP(InstructionArguments&);
void op_INC(InstructionArguments&);
void op_DEC(InstructionArguments&);
void op_SCF(InstructionArguments&);
void op_CCF(InstructionArguments&);

// Arthimetic
void op_ADD(InstructionArguments&);
void op_SUB(InstructionArguments&);
void op_CPL(InstructionArguments&);
void op_CP(InstructionArguments&);
void op_ADC(InstructionArguments&);

void op_AND(InstructionArguments&);
void op_XOR(InstructionArguments&);
void op_OR(InstructionArguments&);

// Rotate and Shift
void op_RLCA(InstructionArguments&);
void op_RLA(InstructionArguments&);
void op_RRCA(InstructionArguments&);
void op_RRA(InstructionArguments&);

// Jumps
void op_JR(InstructionArguments&);
void op_JP(InstructionArguments&);

void op_RST08H(InstructionArguments&);
void op_RST18H(InstructionArguments&);
void op_RST28H(InstructionArguments&);
void op_RST38H(InstructionArguments&);



// SORT THIS!!!
void op_CALL(InstructionArguments&);
void op_XXX(InstructionArguments&);
void op_SBC(InstructionArguments&);
void op_RET(InstructionArguments&);
void op_RETI(InstructionArguments&);
void op_DAA(InstructionArguments&);
void op_PREFIX(InstructionArguments&)
{

}

std::function<void(InstructionArguments&)> Instructions[256] =
{
	op_NOP  , op_LD   , op_LD   , op_INC  , op_INC  , op_DEC  , op_LD   , op_RLCA , op_LD   , op_ADD  , op_LD   , op_DEC   , op_INC  , op_DEC  , op_LD   , op_RRCA ,
	op_STOP , op_LD   , op_LD   , op_INC  , op_INC  , op_DEC  , op_LD   , op_RLA  , op_JR   , op_ADD  , op_LD   , op_DEC   , op_INC  , op_DEC  , op_LD   , op_RRA  ,
	op_JR   , op_LD   , op_LD   , op_INC  , op_INC  , op_DEC  , op_LD   , op_DAA  , op_JR   , op_ADD  , op_LD   , op_DEC   , op_INC  , op_DEC  , op_LD   , op_CPL  ,
	op_JR   , op_LD   , op_LD   , op_INC  , op_INC  , op_DEC  , op_LD   , op_SCF  , op_JR   , op_ADD  , op_LD   , op_DEC   , op_INC  , op_DEC  , op_LD   , op_CCF  ,

	op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD    , op_LD   , op_LD   , op_LD   , op_LD   ,
	op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD    , op_LD   , op_LD   , op_LD   , op_LD   ,
	op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD    , op_LD   , op_LD   , op_LD   , op_LD   ,
	op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_HALT , op_LD   , op_LD   , op_LD   , op_LD   , op_LD    , op_LD   , op_LD   , op_LD   , op_LD   ,

	op_ADD  , op_ADD  , op_ADD  , op_ADD  , op_ADD  , op_ADD  , op_ADD  , op_ADD  , op_ADC  , op_ADC  , op_ADC  , op_ADC   , op_ADC  , op_ADC  , op_ADC  , op_ADC  ,
	op_SUB  , op_SUB  , op_SUB  , op_SUB  , op_SUB  , op_SUB  , op_SUB  , op_SUB  , op_SBC  , op_SBC  , op_SBC  , op_SBC   , op_SBC  , op_SBC  , op_SBC  , op_SBC  ,
	op_AND  , op_AND  , op_AND  , op_AND  , op_AND  , op_AND  , op_AND  , op_AND  , op_XOR  , op_XOR  , op_XOR  , op_XOR   , op_XOR  , op_XOR  , op_XOR  , op_XOR  ,
	op_OR   , op_OR   , op_OR   , op_OR   , op_OR   , op_OR   , op_OR   , op_OR   , op_CP   , op_CP   , op_CP   , op_CP    , op_CP   , op_CP   , op_CP   , op_CP   ,

	op_RET  , op_POP  , op_JP   , op_JP   , op_CALL , op_PUSH , op_ADD  , op_CALL , op_RET  , op_RET  , op_JP   , op_PREFIX, op_CALL , op_CALL , op_ADC  , op_RST08H ,
	op_RET  , op_POP  , op_JP   , op_XXX  , op_CALL , op_PUSH , op_SUB  , op_CALL , op_RET  , op_RETI , op_JP   , op_XXX   , op_CALL , op_XXX  , op_SBC  , op_RST18H ,
	op_LD   , op_POP  , op_LD   , op_XXX  , op_XXX  , op_PUSH , op_AND  , op_CALL , op_ADD  , op_JP   , op_LD   , op_XXX   , op_XXX  , op_XXX  , op_XOR  , op_RST28H ,
	op_LD   , op_POP  , op_LD   , op_DI   , op_XXX  , op_PUSH , op_OR   , op_CALL , op_LD   , op_LD   , op_LD   , op_EI    , op_XXX  , op_XXX  , op_CP   , op_RST38H

};

#pragma region 16-bit Opcodes
void op_RLC(InstructionArguments&);
void op_RRC(InstructionArguments&);

void op_RL(InstructionArguments&);
void op_RR(InstructionArguments&);

void op_SLA(InstructionArguments&);
void op_SRA(InstructionArguments&);
void op_SRL(InstructionArguments&);


void op_SWAP(InstructionArguments&);

void op_BITX(InstructionArguments&);
void op_RESX(InstructionArguments&);
void op_SETX(InstructionArguments&);

std::function<void(InstructionArguments&)> InstructionsCB[256] =
{
	op_RLC , op_RLC , op_RLC , op_RLC , op_RLC , op_RLC , op_RLC , op_RLC , op_RRC , op_RRC , op_RRC , op_RRC , op_RRC , op_RRC , op_RRC , op_RRC ,
	op_RL  , op_RL  , op_RL  , op_RL  , op_RL  , op_RL  , op_RL  , op_RL  , op_RR  , op_RR  , op_RR  , op_RR  , op_RR  , op_RR  , op_RR  , op_RR  ,
	op_SLA , op_SLA , op_SLA , op_SLA , op_SLA , op_SLA , op_SLA , op_SLA , op_SRA , op_SRA , op_SRA , op_SRA , op_SRA , op_SRA , op_SRA , op_SRA ,
	op_SWAP, op_SWAP, op_SWAP, op_SWAP, op_SWAP, op_SWAP, op_SWAP, op_SWAP, op_SRL , op_SRL , op_SRL , op_SRL , op_SRL , op_SRL , op_SRL , op_SRL ,

	op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX,
	op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX,
	op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX,
	op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX, op_BITX,

	op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX,
	op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX,
	op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX,
	op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX, op_RESX,

	op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX,
	op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX,
	op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX,
	op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX, op_SETX,
};



void op_RLC(InstructionArguments& args)
{
	Processor& processor = args.Processor();
	OperandType destType = args.GetLeftHandOperand();
	uint16_t source = 0;

	if (destType == OperandType::RegisterHLIndirect)
		source = processor.GetMemoryBus()->Read(processor.GetRegister(Register::HL));
	else
		source = processor.GetRegister(static_cast<Register>(static_cast<uint8_t>(destType) - 1));

	uint16_t result = source << 1;
	result |= ((result & 0x100) >> 8);

	if (destType == OperandType::RegisterHLIndirect)
		processor.GetMemoryBus()->Write(processor.GetRegister(Register::HL), result & 0xFF);
	else
		processor.SetRegister(static_cast<Register>((static_cast<uint8_t>(destType) - 1)), result);
	

	processor.SetFlag(Processor::FLAGS::Z, result == 0);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, result & (0b1 << 7));
}
void op_RRC(InstructionArguments& args)
{
	Processor& processor = args.Processor();
	OperandType destType = args.GetLeftHandOperand();
	uint16_t source = 0;

	if (destType == OperandType::RegisterHLIndirect)
		source = processor.GetMemoryBus()->Read(processor.GetRegister(Register::HL));
	else
		source = processor.GetRegister(static_cast<Register>(static_cast<uint8_t>(destType) - 1));

	uint16_t result = (source >> 1);

	result |= ((source & (0b1 << 7)) >> 7);

	if (destType == OperandType::RegisterHLIndirect)
		processor.GetMemoryBus()->Write(processor.GetRegister(Register::HL), result & 0xFF);
	else
		processor.SetRegister(static_cast<Register>((static_cast<uint8_t>(destType) - 1)), result);

	processor.SetFlag(Processor::FLAGS::Z, result == 0);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, result & (0b1));
}

void op_RL(InstructionArguments& args)
{
	Processor& processor = args.Processor();
	OperandType destType = args.GetLeftHandOperand();
	uint16_t source = 0;

	if (destType == OperandType::RegisterHLIndirect)
		source = processor.GetMemoryBus()->Read(processor.GetRegister(Register::HL));
	else
		source = processor.GetRegister(static_cast<Register>(static_cast<uint8_t>(destType) - 1));

	uint16_t result = (source << 1) | (processor.GetFlag(Processor::FLAGS::C));


	if (destType == OperandType::RegisterHLIndirect)
		processor.GetMemoryBus()->Write(processor.GetRegister(Register::HL), result & 0xFF);
	else
		processor.SetRegister(static_cast<Register>((static_cast<uint8_t>(destType) - 1)), result);


	processor.SetFlag(Processor::FLAGS::Z, result == 0);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, source & (0b1 << 7));
}

void op_RR(InstructionArguments& args)
{
	Processor& processor = args.Processor();
	OperandType destType = args.GetLeftHandOperand();
	uint16_t source = 0;

	if (destType == OperandType::RegisterHLIndirect)
		source = processor.GetMemoryBus()->Read(processor.GetRegister(Register::HL));
	else
		source = processor.GetRegister(static_cast<Register>(static_cast<uint8_t>(destType) - 1));

	uint16_t result = (source >> 1) | (processor.GetFlag(Processor::FLAGS::C) << 7);

	if (destType == OperandType::RegisterHLIndirect)
		processor.GetMemoryBus()->Write(processor.GetRegister(Register::HL), result & 0xFF);
	else
		processor.SetRegister(static_cast<Register>((static_cast<uint8_t>(destType) - 1)), result);

	processor.SetFlag(Processor::FLAGS::Z, result == 0);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, source & (0b1));
}

void op_SLA(InstructionArguments& args)
{
	Processor& processor = args.Processor();
	OperandType destType = args.GetLeftHandOperand();
	uint16_t source = 0;

	if (destType == OperandType::RegisterHLIndirect)
		source = processor.GetMemoryBus()->Read(processor.GetRegister(Register::HL));
	else
		source = processor.GetRegister(static_cast<Register>(static_cast<uint8_t>(destType) - 1));

	uint16_t result = (source << 1);

	if (destType == OperandType::RegisterHLIndirect)
		processor.GetMemoryBus()->Write(processor.GetRegister(Register::HL), result & 0xFF);
	else
		processor.SetRegister(static_cast<Register>((static_cast<uint8_t>(destType) - 1)), result);

	processor.SetFlag(Processor::FLAGS::Z, result == 0);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, source & (0b1 << 7));
}
void op_SRA(InstructionArguments& args)
{
	Processor& processor = args.Processor();
	OperandType destType = args.GetLeftHandOperand();
	uint16_t source = 0;

	if (destType == OperandType::RegisterHLIndirect)
		source = processor.GetMemoryBus()->Read(processor.GetRegister(Register::HL));
	else
		source = processor.GetRegister(static_cast<Register>(static_cast<uint8_t>(destType) - 1));

	uint16_t result = (source >> 1) | (source & 0b10000000);

	if (destType == OperandType::RegisterHLIndirect)
		processor.GetMemoryBus()->Write(processor.GetRegister(Register::HL), result & 0xFF);
	else
		processor.SetRegister(static_cast<Register>((static_cast<uint8_t>(destType) - 1)), result);

	processor.SetFlag(Processor::FLAGS::Z, result == 0);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, source & (0b1));
}
void op_SRL(InstructionArguments& args)
{
	Processor& processor = args.Processor();
	OperandType destType = args.GetLeftHandOperand();
	uint16_t source = 0;

	if (destType == OperandType::RegisterHLIndirect)
		source = processor.GetMemoryBus()->Read(processor.GetRegister(Register::HL));
	else
		source = processor.GetRegister(static_cast<Register>(static_cast<uint8_t>(destType) - 1));

	uint16_t result = (source >> 1);

	if (destType == OperandType::RegisterHLIndirect)
		processor.GetMemoryBus()->Write(processor.GetRegister(Register::HL), result & 0xFF);
	else
		processor.SetRegister(static_cast<Register>((static_cast<uint8_t>(destType) - 1)), result);

	processor.SetFlag(Processor::FLAGS::Z, result == 0);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, source & (0b1));
}

void op_SWAP(InstructionArguments& args)
{
	Processor& processor = args.Processor();
	OperandType destType = args.GetLeftHandOperand();
	uint16_t source = 0;

	if (destType == OperandType::RegisterHLIndirect)
		source = processor.GetMemoryBus()->Read(processor.GetRegister(Register::HL));
	else
		source = processor.GetRegister(static_cast<Register>(static_cast<uint8_t>(destType) - 1));


	uint8_t result = ((source & 0b1111) << 4) | ((source & 0b11110000) >> 4);

	if (destType == OperandType::RegisterHLIndirect)
		processor.GetMemoryBus()->Write(processor.GetRegister(Register::HL), result & 0xFF);
	else
		processor.SetRegister(static_cast<Register>((static_cast<uint8_t>(destType) - 1)), result);

	processor.SetFlag(Processor::FLAGS::Z, result == 0);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, false);
}

void op_BITX(InstructionArguments& args)
{
	Processor& processor = args.Processor();
	OperandType destType = args.GetLeftHandOperand();
	uint16_t source = 0;

	if (destType == OperandType::RegisterHLIndirect)
		source = processor.GetMemoryBus()->Read(processor.GetRegister(Register::HL));
	else
		source = processor.GetRegister(static_cast<Register>(static_cast<uint8_t>(destType) - 1));

	// Get our bit target
	uint8_t bit = (args.OpCodeInfo().GetHexCode() - 0x40) / 8;

	processor.SetFlag(Processor::FLAGS::Z, !((source & ( 0b1 << bit)) >> bit));
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, true);
}

void op_RESX(InstructionArguments& args)
{
	Processor& processor = args.Processor();
	OperandType destType = args.GetLeftHandOperand();
	uint16_t source = 0;

	if (destType == OperandType::RegisterHLIndirect)
		source = processor.GetMemoryBus()->Read(processor.GetRegister(Register::HL));
	else
		source = processor.GetRegister(static_cast<Register>(static_cast<uint8_t>(destType) - 1));

	// Get our bit target
	uint8_t bit = (args.OpCodeInfo().GetHexCode() - 0x80) / 8;

	uint8_t result = source & ~static_cast<uint8_t>(0b1 << bit);

	if (destType == OperandType::RegisterHLIndirect)
		processor.GetMemoryBus()->Write(processor.GetRegister(Register::HL), result & 0xFF);
	else
		processor.SetRegister(static_cast<Register>((static_cast<uint8_t>(destType) - 1)), result);
}

void op_SETX(InstructionArguments& args)
{
	Processor& processor = args.Processor();
	OperandType destType = args.GetLeftHandOperand();
	uint16_t source = 0;

	if (destType == OperandType::RegisterHLIndirect)
		source = processor.GetMemoryBus()->Read(processor.GetRegister(Register::HL));
	else
		source = processor.GetRegister(static_cast<Register>(static_cast<uint8_t>(destType) - 1));

	// Get our bit target
	uint8_t bit = (args.OpCodeInfo().GetHexCode() - 0xC0) / 8;

	uint8_t result = source | static_cast<uint8_t>(0b1 << bit);

	if (destType == OperandType::RegisterHLIndirect)
		processor.GetMemoryBus()->Write(processor.GetRegister(Register::HL), result & 0xFF);
	else
		processor.SetRegister(static_cast<Register>((static_cast<uint8_t>(destType) - 1)), result);
}
#pragma endregion

#pragma region Misc

void op_NOP(InstructionArguments& args)
{
	// Do Nothing
}

void op_STOP(InstructionArguments& args)
{
	std::cout << "*** op_STOP NOT YET IMPLEMENTED!! ***" << std::endl;
	// TODO
}

void op_HALT(InstructionArguments& args)
{
	args.Processor().Halted = true;
}

void op_EI(InstructionArguments& args)
{
	args.Processor().InterruptMasterEnable = true;
}

void op_DI(InstructionArguments& args)
{
	args.Processor().InterruptMasterEnable = false;
}

void op_SCF(InstructionArguments& args)
{
	Processor& processor = args.Processor();

	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, true);
}
void op_CCF(InstructionArguments& args)
{
	Processor& processor = args.Processor();

	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, !processor.GetFlag(Processor::FLAGS::C));
}
#pragma endregion

void op_LD(InstructionArguments& args)
{
	Processor& processor = args.Processor();

	uint16_t result = args.GetRightHandValue();

	if (args.GetRightHandOperand() == OperandType::AddressUINT8)
		result = args.MemoryBus().Read(0xFF00 + result);

	switch (args.GetLeftHandOperand())
	{
	case OperandType::None:
		break;
	case OperandType::Acculumator:
	case OperandType::RegisterB:
	case OperandType::RegisterC:
	case OperandType::RegisterD:
	case OperandType::RegisterE:
	case OperandType::RegisterH:
	case OperandType::RegisterL:
		processor.SetRegister((Register)((uint16_t)(args.GetLeftHandOperand()) - 1), result & 0xFF);
		break;

	case OperandType::RegisterAF:
	case OperandType::RegisterBC:
	case OperandType::RegisterDE:
	case OperandType::RegisterHL:
	case OperandType::Stackpointer:
	case OperandType::ProgramCounter:
		processor.SetRegister((Register)((uint16_t)(args.GetLeftHandOperand()) - 1), result & 0xFFFF);
		break;

		
	case OperandType::RegisterCIndirect:
		processor.SetDestinationValue(0xFF00 + processor.GetRegister(Register::C), result);
		break;
	case OperandType::RegisterBCIndirect:
		processor.SetDestinationValue(processor.GetRegister(Register::BC), result);
		break;
	case OperandType::RegisterDEIndirect:
		processor.SetDestinationValue(processor.GetRegister(Register::DE), result);
		break;
	case OperandType::RegisterHLIndirect:
		processor.SetDestinationValue(processor.GetRegister(Register::HL), result);
		break;


	case OperandType::IncrementHL:
		processor.SetDestinationValue(processor.GetRegister(Register::HL) - 1, result);
		break;
	case OperandType::DecrementHL:
		processor.SetDestinationValue(processor.GetRegister(Register::HL) + 1, result);
		break;


	case OperandType::DataUINT8:
	case OperandType::DataUINT16:
		std::cout << "LD should never target DataUINT8, DataInt8, OR DataUint16!!" << std::endl;
		break;

	case OperandType::AddressUINT8:
		processor.SetDestinationValue(0xFF00 + args.GetLeftHandValue(), result);
		break;
	case OperandType::AddressUINT16:
		processor.SetDestinationValue(args.GetLeftHandValue(), result);
		break;
	}

}

void op_PUSH(InstructionArguments& args)
{
	args.Processor().StackPush(args.Processor().GetRegister(static_cast<Register>((static_cast<uint8_t>(args.GetLeftHandOperand()) - 1))));
}

void op_POP(InstructionArguments& args)
{
	args.Processor().SetRegister((Register)((uint16_t)(args.GetLeftHandOperand())-1), args.Processor().StackPop());
}

#pragma region Arthimetic
void op_INC(InstructionArguments& args)
{
	Processor& processor = args.Processor();

	uint16_t src = 0;
	uint16_t result = 0;

	Register reg = Register::A;
	reg = (Register)((uint16_t)((OperandType)args.GetLeftHandOperand()) - 1);
	src = processor.GetRegister(reg);
	result = src + 1;

	switch (args.GetLeftHandOperand())
	{
	case OperandType::None:
		break;
	case OperandType::Acculumator:
	case OperandType::RegisterB:
	case OperandType::RegisterC:
	case OperandType::RegisterD:
	case OperandType::RegisterE:
	case OperandType::RegisterH:
	case OperandType::RegisterL:
		result &= 0xFF;
		processor.SetRegister(reg, result);
		processor.SetFlag(Processor::FLAGS::Z, result == 0);
		processor.SetFlag(Processor::FLAGS::N, false);
		processor.SetFlag(Processor::FLAGS::H, (result & 0b1000) != 0);
		break;
	case OperandType::RegisterAF:
	case OperandType::RegisterBC:
	case OperandType::RegisterDE:
	case OperandType::RegisterHL:
	case OperandType::Stackpointer:
	case OperandType::ProgramCounter:
		result &= 0xFFFF;
		processor.SetRegister(reg, result);
		processor.SetFlag(Processor::FLAGS::Z, result == 0);
		processor.SetFlag(Processor::FLAGS::N, false);
		processor.SetFlag(Processor::FLAGS::H, (result & 0b1000) != 0);
		break;
	}
}
void op_DEC(InstructionArguments& args)
{
	Processor& processor = args.Processor();

	uint16_t src = 0;
	uint16_t result = 0;

	Register reg = Register::A;

	reg = (Register)((uint16_t)((OperandType)args.GetLeftHandOperand()) - 1);
	src = processor.GetRegister(reg);
	result = src - 1;

	switch (args.GetLeftHandOperand())
	{
	case OperandType::None:
		break;
	case OperandType::Acculumator:
	case OperandType::RegisterB:
	case OperandType::RegisterC:
	case OperandType::RegisterD:
	case OperandType::RegisterE:
	case OperandType::RegisterH:
	case OperandType::RegisterL:
		result &= 0xFF;
		processor.SetRegister(reg, result);
		processor.SetFlag(Processor::FLAGS::Z, result == 0);
		processor.SetFlag(Processor::FLAGS::N, true);
		processor.SetFlag(Processor::FLAGS::H, (result & 0b1000) != 0);
		break;
	case OperandType::RegisterAF:
	case OperandType::RegisterBC:
	case OperandType::RegisterDE:
	case OperandType::RegisterHL:
	case OperandType::Stackpointer:
	case OperandType::ProgramCounter:
		result &= 0xFFFF;
		processor.SetRegister(reg, result);
		processor.SetFlag(Processor::FLAGS::Z, result == 0);
		processor.SetFlag(Processor::FLAGS::N, true);
		processor.SetFlag(Processor::FLAGS::H, (result & 0b1000) != 0);
		break;
	}
}

void op_CPL(InstructionArguments& args)
{
	Processor& processor = args.Processor();

	processor.SetRegister(Register::A, (~processor.GetRegister(Register::A)) & 0xFF);
	processor.SetFlag(Processor::FLAGS::N, true);
	processor.SetFlag(Processor::FLAGS::H, true);
}
void op_CP(InstructionArguments& args)
{
	Processor& processor = args.Processor();

	uint8_t result = processor.GetRegister(Register::A) - args.GetRightHandValue();

	processor.SetFlag(Processor::FLAGS::Z, result == 0);
	processor.SetFlag(Processor::FLAGS::N, true);
	processor.SetFlag(Processor::FLAGS::H, (result & 0b1000) != 0);
	processor.SetFlag(Processor::FLAGS::C, (result & 0b10000000) != 0);
}

void op_ADD(InstructionArguments& args)
{
	Processor& processor = args.Processor();

	uint16_t source = args.GetRightHandValue();

	uint16_t a = 0;
	uint16_t hl = 0;
	uint16_t sp = 0;
	switch (args.GetLeftHandOperand())
	{
	case OperandType::Acculumator:
		a = processor.GetRegister(Register::A);
		processor.SetRegister(Register::A, (a + source) & 0xFF);
		processor.SetFlag(Processor::FLAGS::Z, a + source == 0);
		processor.SetFlag(Processor::FLAGS::N, false);
		processor.SetFlag(Processor::FLAGS::H, (a + source) > 0x7F);
		processor.SetFlag(Processor::FLAGS::C, (a + source) > 0xFF);
		break;

	case OperandType::RegisterHL:
		hl = processor.GetRegister(Register::HL);
		processor.SetRegister(Register::HL, (hl + source) & 0xFFFF);
		processor.SetFlag(Processor::N, false);
		processor.SetFlag(Processor::H, (hl + source) > 0x7FFF);
		processor.SetFlag(Processor::C, (hl + source) > 0xFFFF);
		break;

	case OperandType::Stackpointer:
		sp = processor.GetRegister(Register::SP);
		processor.SetRegister(Register::SP, (sp + (int8_t)source) & 0xFFFF);
		processor.SetFlag(Processor::Z, false);
		processor.SetFlag(Processor::N, false);
		processor.SetFlag(Processor::H, (sp + (int8_t)source) > 0x7FFF);
		processor.SetFlag(Processor::C, (sp + (int8_t)source) > 0xFFFF);
		break;
	}
}
void op_SUB(InstructionArguments& args)
{
	Processor& processor = args.Processor();

	switch (args.GetLeftHandOperand())
	{
	case OperandType::Acculumator:
		uint16_t a = processor.GetRegister(Register::A);
		processor.SetRegister(Register::A, (a - args.GetRightHandValue()) & 0xFF);
		processor.SetFlag(Processor::FLAGS::Z, a - args.GetRightHandValue() == 0);
		processor.SetFlag(Processor::FLAGS::N, true);
		processor.SetFlag(Processor::FLAGS::H, (a - args.GetRightHandValue()) > 0x7F);
		processor.SetFlag(Processor::FLAGS::C, (a - args.GetRightHandValue()) > 0xFF);
		break;
	}
}

void op_ADC(InstructionArguments& args)
{
	Processor& processor = args.Processor();

	uint8_t c = processor.GetFlag(Processor::FLAGS::C);

	uint8_t pre = processor.GetRegister(Register::A) & 0xFF;
	uint8_t post = (pre + args.GetRightHandValue()) + c;

	processor.SetRegister(Register::A, post);
	processor.SetFlag(Processor::FLAGS::Z, post == 0);
	processor.SetFlag(Processor::FLAGS::N, true);
	processor.SetFlag(Processor::FLAGS::H, post <= 0x7F && pre > 0x7F);
	processor.SetFlag(Processor::FLAGS::C, post <= 0xFF && pre > 0xFF);
}
void op_SBC(InstructionArguments& args)
{
	Processor& processor = args.Processor();

	uint8_t result = (processor.GetRegister(Register::A) - args.GetRightHandValue()) - processor.GetFlag(Processor::FLAGS::C);

	processor.SetRegister(Register::A, result);
	processor.SetFlag(Processor::FLAGS::Z, result == 0);
	processor.SetFlag(Processor::FLAGS::N, true);
	processor.SetFlag(Processor::FLAGS::H, (result & 0b1000) != 0);
	processor.SetFlag(Processor::FLAGS::C, (result & 0b10000000) != 0);
}

void op_DAA(InstructionArguments& args)
{
	Processor& processor = args.Processor();

	uint8_t _a = processor.GetRegister(Register::A);


	if ((_a & 0x0F) > 0x09 || processor.GetFlag(Processor::FLAGS::H)) { _a += 0x06; }
	if ((_a & 0xF0) > 0x90 || processor.GetFlag(Processor::FLAGS::C))
	{
		_a += 0x60;
		processor.SetFlag(Processor::FLAGS::C, true);
	}
	else { processor.SetFlag(Processor::FLAGS::C, false); }

}
#pragma endregion

void op_AND(InstructionArguments& args)
{
	Processor& processor = args.Processor();

	uint8_t result = (args.GetLeftHandValue() | args.GetRightHandValue()) & 0xFF;

	processor.SetRegister(Register::A, result);
	processor.SetFlag(Processor::FLAGS::Z, result == 0);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, true);
	processor.SetFlag(Processor::FLAGS::C, false);
}
void op_XOR(InstructionArguments& args)
{
	Processor& processor = args.Processor();

	uint8_t result = (args.GetLeftHandValue() ^ args.GetRightHandValue()) & 0xFF;

	processor.SetRegister(Register::A, result);
	processor.SetFlag(Processor::FLAGS::Z, result == 0);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, false);
}
void op_OR(InstructionArguments& args)
{
	Processor& processor = args.Processor();

	uint8_t result = (args.GetLeftHandValue() | args.GetRightHandValue()) & 0xFF;

	processor.SetRegister(Register::A, result);
	processor.SetFlag(Processor::FLAGS::Z, result == 0);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, false);
}
#pragma region Rotate and Shift
void op_RLCA(InstructionArguments& args)
{
	Processor& processor = args.Processor();

	uint16_t a = processor.GetRegister(Register::A);
	processor.SetRegister(Register::A, ((a << 1) & 0xFF) | (a & 0x1));
	processor.SetFlag(Processor::FLAGS::Z, false);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, a & (0b1 << 7));
}
void op_RLA(InstructionArguments& args)
{
	Processor& processor = args.Processor();

	uint8_t a = (processor.GetRegister(Register::A) << 1);
	processor.SetRegister(Register::A, a | processor.GetFlag(Processor::FLAGS::C));
	processor.SetFlag(Processor::FLAGS::Z, false);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, a & (0b1 << 7));
}
void op_RRCA(InstructionArguments& args)
{
	Processor& processor = args.Processor();

	uint16_t a = processor.GetRegister(Register::A);
	processor.SetRegister(Register::A, ((a >> 1) & 0xFF));
	processor.SetFlag(Processor::FLAGS::Z, false);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, (a & 0b1));
}
void op_RRA(InstructionArguments& args)
{
	Processor& processor = args.Processor();

	uint16_t a = processor.GetRegister(Register::A);
	processor.SetRegister(Register::A, ((processor.GetFlag(Processor::FLAGS::C) << 7) | ((a >> 1) & 0xFF)) & 0xFF);
	processor.SetFlag(Processor::FLAGS::Z, false);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, (a & 0b1));
}

#pragma endregion

#pragma region Region Program Flow
void op_JR(InstructionArguments& args)
{
	Processor& processor = args.Processor();

	if (args.GetLeftHandOperand() == OperandType::None || args.GetLeftHandValue() == true)
	{
		uint16_t result = processor.GetRegister(Register::PC) + ((int8_t)args.GetRightHandValue());

		processor.SetRegister(Register::PC, result);
	}
}

void op_JP(InstructionArguments& args)
{
	Processor& processor = args.Processor();

	if (args.GetLeftHandOperand() == OperandType::None || args.GetLeftHandValue() == true)
	{
		processor.SetRegister(Register::PC, args.GetRightHandValue());
	}
}
void op_CALL(InstructionArguments& args)
{
	Processor& processor = args.Processor();

	if (args.GetLeftHandOperand() == OperandType::None || args.GetLeftHandValue() == true)
	{
		processor.StackPush(processor.GetRegister(Register::PC));
		processor.SetRegister(Register::PC, args.GetRightHandValue());
	}
}

void op_RET(InstructionArguments& args)
{
	args.Processor().SetRegister(Register::PC, args.Processor().StackPop()); // dest = [sp]
}

void op_RETI(InstructionArguments& args)
{
	args.Processor().SetRegister(Register::PC, args.Processor().StackPop()); // dest = [sp]
	args.Processor().InterruptMasterEnable = true;
}

void op_RST08H(InstructionArguments& args)
{
	args.Processor().ResetVector(0x08);
}
void op_RST18H(InstructionArguments& args)
{
	args.Processor().ResetVector(0x18);
}
void op_RST28H(InstructionArguments& args)
{
	args.Processor().ResetVector(0x28);
}
void op_RST38H(InstructionArguments& args)
{
	args.Processor().ResetVector(0x38);
}

#pragma endregion

void op_XXX(InstructionArguments& args)
{
	std::cout << "**** ILLEGAL INSTRUCTION! *****" << std::endl;
	std::cout << "PC: " << std::to_string(args.Processor().GetRegister(Register::PC)) << std::endl;
	std::cout << "*******************************" << std::endl;
	// This locks the processor but ignoring it doesn't break anything
}