#include "Processor.hpp"
#include "MemoryBus.hpp"

void op_0x00(Processor&, std::uint16_t);
void op_0x01(Processor&, std::uint16_t);
void op_0x02(Processor&, std::uint16_t);
void op_0x03(Processor&, std::uint16_t);
void op_0x04(Processor&, std::uint16_t);
void op_0x05(Processor&, std::uint16_t);
void op_0x06(Processor&, std::uint16_t);
void op_0x07(Processor&, std::uint16_t);
void op_0x08(Processor&, std::uint16_t);
void op_0x09(Processor&, std::uint16_t);
void op_0x0A(Processor&, std::uint16_t);
void op_0x0B(Processor&, std::uint16_t);
void op_0x0C(Processor&, std::uint16_t);
void op_0x0D(Processor&, std::uint16_t);
void op_0x0E(Processor&, std::uint16_t);
void op_0x0F(Processor&, std::uint16_t);

std::function<void(Processor&, std::uint16_t)> Instructions[256] =
{
	op_0x00, op_0x01, op_0x02, op_0x03, op_0x04, op_0x05, op_0x06, op_0x07, op_0x08, op_0x09, op_0x0A, op_0x0B, op_0x0C, op_0x0D, op_0x0E, op_0x0F,
};

#pragma region Operations 0x00 - 0x0F
// NOP
void op_0x00(Processor& processor, std::uint16_t source)
{
	// do nothing
}

// LD BC,d16
void op_0x01(Processor& processor, std::uint16_t source)
{
	processor.SetDestinationValue(Register::BC, source);
}

// LD (BC),A
void op_0x02(Processor& processor, std::uint16_t source)
{
	processor.SetDestinationValue(Register::BC, source, false);
}

// INC BC
void op_0x03(Processor& processor, std::uint16_t source)
{
	processor.SetDestinationValue(Register::BC, (source + 1) % 0xFFFF);
}

// INC B
void op_0x04(Processor& processor, std::uint16_t source)
{
	processor.SetDestinationValue(Register::B, (source + 1) % 0xFF);
	processor.SetFlag(Processor::FLAGS::Z, source == 0xFF);
	processor.SetFlag(Processor::FLAGS::N, false);
	processor.SetFlag(Processor::FLAGS::H, source == 0xFF);
}

// DEC B
void op_0x05(Processor& processor, std::uint16_t source)
{
	processor.SetDestinationValue(Register::B, (source - 1) % 0xFF);
	processor.SetFlag(Processor::FLAGS::Z, source == 0x1);
	processor.SetFlag(Processor::FLAGS::N, true);
	processor.SetFlag(Processor::FLAGS::H, source == 0x00);
}

// LD B,d8
void op_0x06(Processor& processor, std::uint16_t source)
{
	processor.SetDestinationValue(Register::B, source);
}

// RLCA
void op_0x07(Processor& processor, std::uint16_t source)
{
	processor.SetDestinationValue(Register::A, (source << 1));
	processor.SetFlag(Processor::FLAGS::Z, 0);
	processor.SetFlag(Processor::FLAGS::N, 0);
	processor.SetFlag(Processor::FLAGS::H, 0);
	processor.SetFlag(Processor::FLAGS::C, source & 0b10000000);
}


void op_0x08(Processor& processor, std::uint16_t source)
{

}


void op_0x09(Processor& processor, std::uint16_t source)
{

}


void op_0x0A(Processor& processor, std::uint16_t source)
{

}


void op_0x0B(Processor& processor, std::uint16_t source)
{

}


void op_0x0C(Processor& processor, std::uint16_t source)
{

}


void op_0x0D(Processor& processor, std::uint16_t source)
{

}


void op_0x0E(Processor& processor, std::uint16_t source)
{

}


void op_0x0F(Processor& processor, std::uint16_t source)
{

}
#pragma endregion