#include "Processor.hpp"
#include "MemoryBus.hpp"

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

// Rotate and Shift
void op_RLCA(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_RLA(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_RRCA(Processor&, OperandType, std::uint16_t, std::uint16_t);
void op_RRA(Processor&, OperandType, std::uint16_t, std::uint16_t);

// Jumps
void op_JR(Processor&, OperandType, std::uint16_t, std::uint16_t);

std::function<void(Processor&, OperandType, std::uint16_t, std::uint16_t)> Instructions[256] =
{
	op_NOP  , op_LD   , op_LD   , op_INC  , op_INC  , op_DEC  , op_LD   , op_RLCA , op_LD   , op_ADD  , op_LD   , op_DEC  , op_INC  , op_DEC  , op_LD   , op_RRCA ,
	op_STOP , op_LD   , op_LD   , op_INC  , op_INC  , op_DEC  , op_LD   , op_RLA  , op_JR   , op_ADD  , op_LD   , op_DEC  , op_INC  , op_DEC  , op_LD   , op_RRA  ,
	op_JR   , op_LD   , op_LD   , op_INC  , op_INC  , op_DEC  , op_LD   , op_DAA  , op_JR   , op_ADD  , op_LD   , op_DEC  , op_INC  , op_DEC  , op_LD   , op_CPL  ,
	op_JR   , op_LD   , op_LD   , op_INC  , op_INC  , op_DEC  , op_LD   , op_SCF  , op_JR   , op_ADD  , op_LD   , op_DEC  , op_INC  , op_DEC  , op_LD   , op_CCF  ,

	op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   ,
	op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   ,
	op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   ,
	op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_HALT , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   , op_LD   ,
	op_ADD  , op_ADD  , op_ADD  , op_ADD  , op_ADD  , op_ADD  , op_ADD  , op_ADD  , op_ADC  , op_ADC  , op_ADC  , op_ADC  , op_ADC  , op_ADC  , op_ADC  , op_ADC  ,
	op_SUB  , op_SUB  , op_SUB  , op_SUB  , op_SUB  , op_SUB  , op_SUB  , op_SUB  , op_SBC  , op_SBC  , op_SBC  , op_SBC  , op_SBC  , op_SBC  , op_SBC  , op_SBC  ,
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
	processor.ime = true;
}

void op_DI(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	processor.ime = false;
}
void op_SCF(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, false);
	processor.SetFlag(Processor::FLAGS::C, true);
}
void op_SCF(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
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
		processor.SetDestinationValue(0xFF + processor.GetRegister(Register::C), source, false);
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
	// TODO
}

void op_POP(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	// TODO
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

void op_ADD(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	switch (destType)
	{
	case OperandType::Acculumator:
		uint16_t a = processor.GetRegister(Register::A);
		processor.SetRegister(Register::A, (a + source) & 0xFF);
		processor.SetFlag(Processor::FLAGS::Z, a + source == 0);
		processor.SetFlag(Processor::FLAGS::N, false);
		processor.SetFlag(Processor::FLAGS::H, (a + source) > 0xFF);
		processor.SetFlag(Processor::FLAGS::C, (a + source) > 0xFF);
		break;

	case OperandType::RegisterHL:
		uint16_t hl = processor.GetRegister(Register::HL);
		processor.SetRegister(Register::HL, (hl + source) & 0xFFFF);
		processor.SetFlag(Processor::N, false);
		processor.SetFlag(Processor::H, (hl + source) > 0xFFFF);
		processor.SetFlag(Processor::C, (hl + source) > 0xFFFF);
		break;

	case OperandType::Stackpointer:
		uint16_t sp = processor.GetRegister(Register::SP);
		processor.SetRegister(Register::SP, (sp + (int8_t)source) & 0xFFFF);
		processor.SetFlag(Processor::Z, false);
		processor.SetFlag(Processor::N, false);
		processor.SetFlag(Processor::H, (sp + (int8_t)source) > 0xFFFF);
		processor.SetFlag(Processor::C, (sp + (int8_t)source) > 0xFFFF);
		break;
	}
}
void op_DEC(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{
	switch (destType)
	{
	case OperandType::Acculumator:
		uint16_t a = processor.GetRegister(Register::A);
		processor.SetRegister(Register::A, (a - source) & 0xFF);
		processor.SetFlag(Processor::FLAGS::Z, a - source == 0);
		processor.SetFlag(Processor::FLAGS::N, true);
		processor.SetFlag(Processor::FLAGS::H, (a - source) > 0xFF);
		processor.SetFlag(Processor::FLAGS::C, (a - source) > 0xFF);
		break;
	}
}

void op_ADC(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{

}
void op_SBC(Processor& processor, OperandType destType, std::uint16_t dest, std::uint16_t source)
{

}
#pragma endregion

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
