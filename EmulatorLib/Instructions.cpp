#include "Processor.hpp"
#include "MemoryBus.hpp"

void op_0x00(Processor&, MemoryBus*, std::uint16_t);
void op_0x01(Processor&, MemoryBus*, std::uint16_t);
void op_0x02(Processor&, MemoryBus*, std::uint16_t);
void op_0x03(Processor&, MemoryBus*, std::uint16_t);
void op_0x04(Processor&, MemoryBus*, std::uint16_t);
void op_0x05(Processor&, MemoryBus*, std::uint16_t);
void op_0x06(Processor&, MemoryBus*, std::uint16_t);
void op_0x07(Processor&, MemoryBus*, std::uint16_t);
void op_0x08(Processor&, MemoryBus*, std::uint16_t);
void op_0x09(Processor&, MemoryBus*, std::uint16_t);
void op_0x0A(Processor&, MemoryBus*, std::uint16_t);
void op_0x0B(Processor&, MemoryBus*, std::uint16_t);
void op_0x0C(Processor&, MemoryBus*, std::uint16_t);
void op_0x0D(Processor&, MemoryBus*, std::uint16_t);
void op_0x0E(Processor&, MemoryBus*, std::uint16_t);
void op_0x0F(Processor&, MemoryBus*, std::uint16_t);

std::function<void(Processor&, MemoryBus*, std::uint16_t)> Instructions[256] =
{
	op_0x00, op_0x01, op_0x02, op_0x03, op_0x04, op_0x05, op_0x06, op_0x07, op_0x08, op_0x09, op_0x0A, op_0x0B, op_0x0C, op_0x0D, op_0x0E, op_0x0F,
};

#pragma region Operations 0x00 - 0x0F
// NOP
void op_0x00(Processor& processor, MemoryBus* bus, std::uint16_t constant)
{
	// do nothing
}

// LD BC,d16
void op_0x01(Processor& processor, MemoryBus* bus, std::uint16_t constant)
{
	processor.SetRegister(Register::BC, constant);
}


void op_0x02(Processor& processor, MemoryBus* bus, std::uint16_t constant)
{
	bus->Write(processor.GetRegister(Register::BC), processor.GetRegister(Register::A));
}


void op_0x03(Processor& processor, MemoryBus* bus, std::uint16_t constant)
{
	processor.SetRegister(Register::BC, (processor.GetRegister(Register::BC) + 1) % 0xFFFF);
}


void op_0x04(Processor& processor, MemoryBus* bus, std::uint16_t constant)
{
	uint8_t value = processor.GetRegister(Register::B);
	processor.SetRegister(Register::B, (value + 1) % 0xFF);
	if (value == 0xFF)
		processor.SetFlag(FLAGS::Z);

}


void op_0x05(Processor& processor, MemoryBus* bus, std::uint16_t constant)
{

}


void op_0x06(Processor& processor, MemoryBus* bus, std::uint16_t constant)
{

}


void op_0x07(Processor& processor, MemoryBus* bus, std::uint16_t constant)
{

}


void op_0x08(Processor& processor, MemoryBus* bus, std::uint16_t constant)
{

}


void op_0x09(Processor& processor, MemoryBus* bus, std::uint16_t constant)
{

}


void op_0x0A(Processor& processor, MemoryBus* bus, std::uint16_t constant)
{

}


void op_0x0B(Processor& processor, MemoryBus* bus, std::uint16_t constant)
{

}


void op_0x0C(Processor& processor, MemoryBus* bus, std::uint16_t constant)
{

}


void op_0x0D(Processor& processor, MemoryBus* bus, std::uint16_t constant)
{

}


void op_0x0E(Processor& processor, MemoryBus* bus, std::uint16_t constant)
{

}


void op_0x0F(Processor& processor, MemoryBus* bus, std::uint16_t constant)
{

}
#pragma endregion