#include "Processor.hpp"
#include "MemoryBus.hpp"

#include <iostream>

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
	// TODO
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
		processor.SetRegister((Register)((uint16_t)(destType) - 8), source & 0xFFFF);
		break;

		
	case OperandType::RegisterCIndirect:
		processor.SetDestinationValue(0xFF00 + processor.GetRegister(Register::C), source, false);
		break;
	case OperandType::RegisterBCIndirect:
		processor.SetDestinationValue(processor.GetRegister(Register::BC), source, false);
		break;
	case OperandType::RegisterDEIndirect:
		processor.SetDestinationValue(processor.GetRegister(Register::DE), source, false);
		break;
	case OperandType::RegisterHLIndirect:
		processor.SetDestinationValue(processor.GetRegister(Register::HL), source, false);
		break;


	case OperandType::IncrementHL:
		processor.SetDestinationValue(processor.GetRegister(Register::HL), (source + 1) & 0xFFFF);
		break;
	case OperandType::DecrementHL:
		processor.SetDestinationValue(processor.GetRegister(Register::HL), (source - 1) & 0xFFFF);
		break;


	case OperandType::DataUINT8:
		break;
	case OperandType::DataUINT16:
		break;

	case OperandType::AddressUINT8:
		break;
	case OperandType::AddressUINT16:

		break;
	case OperandType::DataINT8:
		break;
	}

}

void op_PUSH(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	processor.StackPush(dest);
}

void op_POP(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	processor.SetRegister((Register)((uint16_t)(destType)-1), processor.StackPop()); // dest = [sp]
}

void op_CALL(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	// This doesn't care about conditionals, that needs to be added

	// push pc
	processor.SetDestinationValue(processor.GetRegister(Register::SP), processor.GetRegister(Register::PC));
	processor.SetRegister(Register::SP, (processor.GetRegister(Register::SP) + 2) & 0xFFFF);

	processor.SetRegister(Register::PC, dest);
}

void op_RET(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	// pop pc
	processor.SetRegister(Register::PC, processor.StackPop()); // dest = [sp]
}

void op_RETI(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	// pop pc
	processor.SetRegister(Register::PC, processor.StackPop()); // dest = [sp]
	processor.InterruptMasterEnable = true;
}

#pragma region Arthimetic
void op_INC(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
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
		processor.SetRegister((Register)((uint16_t)((OperandType)destType) - 1), (source + 1) & 0xFF);
		processor.SetFlag(Processor::FLAGS::Z, source == 0xFF);
		processor.SetFlag(Processor::FLAGS::N, false);
		processor.SetFlag(Processor::FLAGS::H, source == 0xFF);
		break;

	case OperandType::RegisterAF:
	case OperandType::RegisterBC:
	case OperandType::RegisterDE:
	case OperandType::RegisterHL:
	case OperandType::Stackpointer:
	case OperandType::ProgramCounter:
		processor.SetRegister((Register)((uint16_t)((OperandType)destType) - 8), (source + 1) & 0xFFFF);
		break;
	}
}
void op_DEC(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
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
		processor.SetRegister((Register)((uint16_t)((OperandType)destType) - 1), (source - 1) & 0xFF);
		processor.SetFlag(Processor::FLAGS::Z, source == 1);
		processor.SetFlag(Processor::FLAGS::N, false);
		processor.SetFlag(Processor::FLAGS::H, source == 0);
		break;

	case OperandType::RegisterAF:
	case OperandType::RegisterBC:
	case OperandType::RegisterDE:
	case OperandType::RegisterHL:
	case OperandType::Stackpointer:
	case OperandType::ProgramCounter:
		processor.SetRegister((Register)((uint16_t)((OperandType)destType) - 8), (source - 1) & 0xFFFF);
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
	uint8_t a = processor.GetRegister(Register::A);

	processor.SetFlag(Processor::FLAGS::Z, a - source == 0);
	processor.SetFlag(Processor::FLAGS::N, true);
	processor.SetFlag(Processor::FLAGS::H, a >= 0x0F && source != 0);
	processor.SetFlag(Processor::FLAGS::C, source > a);
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
	uint8_t c = processor.GetFlag(Processor::FLAGS::C);

	uint8_t pre = processor.GetRegister(Register::A) & 0xFF;
	uint8_t post = (pre - source) - c;

	processor.SetRegister(Register::A, post);
	processor.SetFlag(Processor::FLAGS::Z, post == 0);
	processor.SetFlag(Processor::FLAGS::N, true);
	processor.SetFlag(Processor::FLAGS::H, post <= 0xFF && pre > 0x7F);
	processor.SetFlag(Processor::FLAGS::C, post <= 0xFF && pre > 0xFF);
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
	processor.SetRegister(Register::A, (processor.GetRegister(Register::A) & source) & 0xFF);
}
void op_XOR(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	processor.SetRegister(Register::A, (processor.GetRegister(Register::A) ^ source) & 0xFF);
}
void op_OR(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	processor.SetRegister(Register::A, (processor.GetRegister(Register::A) | source) & 0xFF);
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
	// This locks the processor but ignoring it doesn't break anything
}