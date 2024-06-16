#include "Processor.hpp"
#include "MemoryBus.hpp"
#include "InstructionArguments.hpp"


#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

void op_NOP(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_STOP(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_HALT(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_EI(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_DI(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_LD(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_PUSH(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_POP(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_INC(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_DEC(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_SCF(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_CCF(Processor&, OperandType, std::uint16_t, std::uint16_t);

// Arthimetic
void op_ADD(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_SUB(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_CPL(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_CP(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_ADC(Processor&, OperandType, std::uint16_t, std::uint16_t);

void op_AND(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_XOR(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_OR(Processor&, OperandType, std::uint16_t, std::uint16_t);

// Rotate and Shift
void op_RLCA(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_RLA(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_RRCA(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_RRA(Processor&, OperandType, std::uint16_t, std::uint16_t);

// Jumps
void op_JR(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_JP(Processor&, OperandType, std::uint16_t, std::uint16_t);

void op_RST08H(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_RST18H(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_RST28H(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_RST38H(Processor&, OperandType, std::uint16_t, std::uint16_t);



// SORT THIS!!!
void op_CALL(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_XXX(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_SBC(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_RET(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_RETI(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_DAA(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_PREFIX(Processor&, OperandType, std::uint16_t, std::uint16_t)
{
	// TODO
}

std::function<void(Processor&, OperandType, std::uint16_t, std::uint16_t)> Instructions[256] =
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
void op_RLC(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_RRC(Processor&, OperandType, std::uint16_t, std::uint16_t);

void op_RL(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_RR(Processor&, OperandType, std::uint16_t, std::uint16_t);

void op_SLA(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_SRA(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_SRL(Processor&, OperandType, std::uint16_t, std::uint16_t);

std::function<void(Processor&, OperandType, std::uint16_t, std::uint16_t) > InstructionsCB[256] =
{
	op_RLC, op_RLC, op_RLC, op_RLC, op_RLC, op_RLC, op_RLC, op_RLC, op_RRC, op_RRC, op_RRC, op_RRC, op_RRC, op_RRC, op_RRC, op_RRC,
	op_RL , op_RL , op_RL , op_RL , op_RL , op_RL , op_RL , op_RL , op_RR , op_RR , op_RR , op_RR , op_RR , op_RR , op_RR , op_RR ,
};



void op_RLC(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	Register reg = static_cast<Register>((static_cast<uint8_t>(destType) - 1));

	uint16_t result = source << 1;

	result |= ((result & 0x100) >> 8);

	processor.SetFlag(Processor::FLAGS::Z, result == 0);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, result & (0b1 << 7));
}
void op_RRC(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	Register reg = static_cast<Register>((static_cast<uint8_t>(destType) - 1));

	uint16_t result = (source >> 1);

	result |= ((source & (0b1 << 7)) >> 7);

	processor.SetFlag(Processor::FLAGS::Z, result == 0);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, result & (0b1));
}

void op_RL(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	Register reg = static_cast<Register>((static_cast<uint8_t>(destType) - 1));

	uint16_t result = (source << 1) | (processor.GetFlag(Processor::FLAGS::C));

	processor.SetFlag(Processor::FLAGS::Z, result == 0);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, source & (0b1 << 7));
}

void op_RR(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	Register reg = static_cast<Register>((static_cast<uint8_t>(destType) - 1));

	uint16_t result = (source >> 1) | (processor.GetFlag(Processor::FLAGS::C) << 7);

	processor.SetFlag(Processor::FLAGS::Z, result == 0);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, source & (0b1));
}

void op_SLA(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	Register reg = static_cast<Register>((static_cast<uint8_t>(destType) - 1));

	uint16_t result = (source << 1);

	processor.SetFlag(Processor::FLAGS::Z, result == 0);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, source & (0b1 << 7));
}
void op_SRA(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	Register reg = static_cast<Register>((static_cast<uint8_t>(destType) - 1));

	uint16_t result = (source >> 1);

	processor.SetFlag(Processor::FLAGS::Z, result == 0);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, source & (0b1));
}

#pragma endregion

#pragma region Misc


void op_NOP(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	// Do Nothing
}

void op_STOP(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	// TODO
}

void op_HALT(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	processor.Halted = true;
}

void op_EI(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	processor.InterruptMasterEnable = true;
}

void op_DI(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	processor.InterruptMasterEnable = false;
}

void op_SCF(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, true);
}
void op_CCF(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, !processor.GetFlag(Processor::FLAGS::C));
}
#pragma endregion

void op_LD(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	switch (destType)
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
		processor.SetRegister((Register)((uint16_t)(destType) - 1), source & 0xFF);
		break;

	case OperandType::RegisterAF:
	case OperandType::RegisterBC:
	case OperandType::RegisterDE:
	case OperandType::RegisterHL:
	case OperandType::Stackpointer:
	case OperandType::ProgramCounter:
		processor.SetRegister((Register)((uint16_t)(destType) - 1), source & 0xFFFF);
		break;

		
	case OperandType::RegisterCIndirect:
		processor.SetDestinationValue(0xFF00 + processor.GetRegister(Register::C), source);
		break;
	case OperandType::RegisterBCIndirect:
		processor.SetDestinationValue(processor.GetRegister(Register::BC), source);
		break;
	case OperandType::RegisterDEIndirect:
		processor.SetDestinationValue(processor.GetRegister(Register::DE), source);
		break;
	case OperandType::RegisterHLIndirect:
		processor.SetDestinationValue(processor.GetRegister(Register::HL), source);
		break;


	case OperandType::IncrementHL:
		processor.SetDestinationValue(processor.GetRegister(Register::HL), source);
		processor.SetRegister(Register::HL, (processor.GetRegister(Register::HL) + 1) % 0xFFFF);
		break;
	case OperandType::DecrementHL:
		processor.SetDestinationValue(processor.GetRegister(Register::HL), source);
		processor.SetRegister(Register::HL, (processor.GetRegister(Register::HL) - 1) % 0xFFFF);
		break;


	case OperandType::DataUINT8:
		break;
	case OperandType::DataUINT16:
		break;

	case OperandType::AddressUINT8:
		processor.SetDestinationValue(0xFF00 + dest, source);
		break;
	case OperandType::AddressUINT16:
		processor.SetDestinationValue(dest, source);
		break;
	case OperandType::DataINT8:
		break;
	}

}

void op_PUSH(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	processor.StackPush(processor.GetRegister(static_cast<Register>((static_cast<uint8_t>(destType) - 1))));
}

void op_POP(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	processor.SetRegister((Register)((uint16_t)(destType)-1), processor.StackPop()); // dest = [sp]
}

void op_CALL(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	if (dest)
	{
		processor.StackPush(processor.GetRegister(Register::PC));
		processor.SetRegister(Register::PC, source);
	}
}

void op_RET(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	processor.SetRegister(Register::PC, processor.StackPop()); // dest = [sp]
}

void op_RETI(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	processor.SetRegister(Register::PC, processor.StackPop()); // dest = [sp]
	processor.InterruptMasterEnable = true;
}

#pragma region Arthimetic
void op_INC(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	uint16_t src = 0;
	uint16_t result = 0;

	Register reg = Register::A;
	reg = (Register)((uint16_t)((OperandType)destType) - 1);
	src = processor.GetRegister(reg);
	result = src + 1;

	switch (destType)
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
void op_DEC(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	uint16_t src = 0;
	uint16_t result = 0;

	Register reg = Register::A;

	reg = (Register)((uint16_t)((OperandType)destType) - 1);
	src = processor.GetRegister(reg);
	result = src - 1;

	switch (destType)
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

void op_CPL(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	processor.SetRegister(Register::A, (~processor.GetRegister(Register::A)) & 0xFF);
	processor.SetFlag(Processor::FLAGS::N, true);
	processor.SetFlag(Processor::FLAGS::H, true);
}
void op_CP(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	uint8_t result = processor.GetRegister(Register::A) - source;

	processor.SetFlag(Processor::FLAGS::Z, result == 0);
	processor.SetFlag(Processor::FLAGS::N, true);
	processor.SetFlag(Processor::FLAGS::H, (result & 0b1000) != 0);
	processor.SetFlag(Processor::FLAGS::C, (result & 0b10000000) != 0);
}

void op_ADD(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	uint16_t a = 0;
	uint16_t hl = 0;
	uint16_t sp = 0;
	switch (destType)
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
void op_SUB(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	switch (destType)
	{
	case OperandType::Acculumator:
		uint16_t a = processor.GetRegister(Register::A);
		processor.SetRegister(Register::A, (a - source) & 0xFF);
		processor.SetFlag(Processor::FLAGS::Z, a - source == 0);
		processor.SetFlag(Processor::FLAGS::N, true);
		processor.SetFlag(Processor::FLAGS::H, (a - source) > 0x7F);
		processor.SetFlag(Processor::FLAGS::C, (a - source) > 0xFF);
		break;
	}
}

void op_ADC(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	uint8_t c = processor.GetFlag(Processor::FLAGS::C);

	uint8_t pre = processor.GetRegister(Register::A) & 0xFF;
	uint8_t post = (pre + source) + c;

	processor.SetRegister(Register::A, post);
	processor.SetFlag(Processor::FLAGS::Z, post == 0);
	processor.SetFlag(Processor::FLAGS::N, true);
	processor.SetFlag(Processor::FLAGS::H, post <= 0x7F && pre > 0x7F);
	processor.SetFlag(Processor::FLAGS::C, post <= 0xFF && pre > 0xFF);
}
void op_SBC(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	uint8_t result = (processor.GetRegister(Register::A) - source) - processor.GetFlag(Processor::FLAGS::C);

	processor.SetRegister(Register::A, result);
	processor.SetFlag(Processor::FLAGS::Z, result == 0);
	processor.SetFlag(Processor::FLAGS::N, true);
	processor.SetFlag(Processor::FLAGS::H, (result & 0b1000) != 0);
	processor.SetFlag(Processor::FLAGS::C, (result & 0b10000000) != 0);
}

void op_DAA(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
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

void op_AND(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	uint8_t result = (processor.GetRegister(Register::A) & source) & 0xFF;

	processor.SetRegister(Register::A, result);
	processor.SetFlag(Processor::FLAGS::Z, result == 0);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, true);
	processor.SetFlag(Processor::FLAGS::C, false);
}
void op_XOR(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	uint8_t result = (processor.GetRegister(Register::A) ^ source) & 0xFF;

	processor.SetRegister(Register::A, result);
	processor.SetFlag(Processor::FLAGS::Z, result == 0);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, false);
}
void op_OR(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	uint8_t result = (processor.GetRegister(Register::A) | source) & 0xFF;

	processor.SetRegister(Register::A, result);
	processor.SetFlag(Processor::FLAGS::Z, result == 0);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, false);
}
#pragma region Rotate and Shift
void op_RLCA(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	uint16_t a = processor.GetRegister(Register::A);
	processor.SetRegister(Register::A, ((a << 1) & 0xFF) | (a & 0x1));
	processor.SetFlag(Processor::FLAGS::Z, false);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, (a & 0b1 << 15));
}
void op_RLA(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	uint16_t a = processor.GetRegister(Register::A);
	processor.SetRegister(Register::A, ((a << 1) & 0xFF) | processor.GetFlag(Processor::FLAGS::C));
	processor.SetFlag(Processor::FLAGS::Z, false);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, (a & 0b1 << 15));
}
void op_RRCA(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	uint16_t a = processor.GetRegister(Register::A);
	processor.SetRegister(Register::A, ((a >> 1) & 0xFF));
	processor.SetFlag(Processor::FLAGS::Z, false);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, (a & 0b1));
}
void op_RRA(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	uint16_t a = processor.GetRegister(Register::A);
	processor.SetRegister(Register::A, ((processor.GetFlag(Processor::FLAGS::C) << 7) | ((a >> 1) & 0xFF)) & 0xFF);
	processor.SetFlag(Processor::FLAGS::Z, false);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, (a & 0b1));
}

#pragma endregion

void op_JR(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	if (dest)
		processor.SetRegister(Register::PC, source);
}

void op_JP(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	if (dest)
		processor.SetRegister(Register::PC, source);
}

void op_RST08H(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	processor.ResetVector(0x08);
}
void op_RST18H(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	processor.ResetVector(0x18);
}
void op_RST28H(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	processor.ResetVector(0x28);
}
void op_RST38H(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	processor.ResetVector(0x38);
}

void op_XXX(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{

	std::cout << "**** ILLEGAL INSTRUCTION! *****" << std::endl;
	std::cout << "PC: " << std::to_string(processor.GetRegister(Register::PC)) << std::endl;
	std::cout << "*******************************" << std::endl;
	// This locks the processor but ignoring it doesn't break anything
}