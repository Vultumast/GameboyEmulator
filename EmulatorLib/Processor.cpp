#include "Processor.hpp"
#include "Constants.hpp"
#include "MemoryBus.hpp"



Processor::Processor(MemoryBus* memoryBus)
{
	_memoryBus = memoryBus;
	// TODO: SETUP INSTRUCTION TABLE
	// Maybe make four tables in "blocks" like Pan Docs?
}

uint8_t Processor::read(uint16_t addr)
{
	// read from bus
	return 0;
}

void Processor::write(uint16_t addr, uint8_t value)
{
	// write to bus
}

void Processor::Reset()
{
	pc = 0x0100;
	sp = 0xFFFE;

	// These are values for the DMG model game boy, they're different for GBC
	a = 0x01;
	b = 0x00;
	c = 0x13;
	d = 0x00;
	e = 0xD8;
	f = 0x30; // This is wrong if the header checksum is 0x00 but I don't care
	h = 0x01;
	l = 0x4D;
}

void Processor::interrupt()
{
	// TODO
}

void Processor::nmi()
{
	// TODO
}

void Processor::PulseClock()
{
	_cycleCount = (_cycleCount + 1) % 0xFF;
	_remainingCycles--;

	// Cycle timer finished?
	if (IsInstructionCompleted())
	{
		OpCodeInfo& info = OpCodes[fetch()];


		switch (info.GetOpCode())
		{
		case OpCode::NOP:
			break;
		case OpCode::LD:

			break;
		}


		std::function<void(Processor&, MemoryBus*, uint16_t)>& func = Instructions[info.GetHexCode()];

	}

}

void Processor::SetRegister(Register destination, uint16_t value)
{
	switch (destination)
	{
	case Register::A:
		a = value & 0xFF;
		break;
	case Register::B:
		b = value & 0xFF;
		break;
	case Register::C:
		c = value & 0xFF;
		break;
	case Register::D:
		d = value & 0xFF;
		break;
	case Register::E:
		e = value & 0xFF;
		break;
	case Register::H:
		h = value & 0xFF;
		break;
	case Register::L:
		l = value & 0xFF;
		break;
	case Register::AF:
		a = value & 0xFF >> 8;
		f = value & 0xFF;
		break;
	case Register::BC:
		b = value & 0xFF >> 8;
		c = value & 0xFF;
		break;
	case Register::DE:
		d = value & 0xFF >> 8;
		e = value & 0xFF;
		break;
	case Register::HL:
		h = value & 0xFF >> 8;
		l = value & 0xFF;
		break;
	case Register::SP:
		sp = value;
		break;
	case Register::PC:
		pc = value;
		break;
	}
}
uint16_t Processor::GetRegister(Register destination) const
{
	switch (destination)
	{
	case Register::A:
		return a;
	case Register::B:
		return b;
	case Register::C:
		return c;
	case Register::D:
		return d;
	case Register::E:
		return e;
	case Register::H:
		return h;
	case Register::L:
		return l;
	case Register::AF:
		return static_cast<uint16_t>((a << 8) | (f));
	case Register::BC:
		return static_cast<uint16_t>((b << 8) | (c));
	case Register::DE:
		return static_cast<uint16_t>((d << 8) | (e));
	case Register::HL:
		return static_cast<uint16_t>((h << 8) | (l));
	case Register::SP:
		return sp;
	case Register::PC:
		return pc;
	default:
		return 0xFF;
	}
}

uint8_t Processor::GetFlag(FLAGS flag) const
{
	return ((f & flag) > 0) ? 1 : 0;
}

void Processor::SetFlag(FLAGS flag, bool value)
{
	if (value)
		f |= flag;
	else
		f &= ~flag;
}



uint8_t Processor::fetch()
{
	uint8_t value = _memoryBus->Read(pc);
	pc = (pc + 1) & 0xFFFF;
	return value;
}

void Processor::op_NOP()
{

}

void Processor::op_LD(Register destination, Register source)
{
	SetRegister(destination, GetRegister(source));
}
void Processor::op_LD(uint16_t destination, Register source)
{
	_memoryBus->Write(destination, GetRegister(source));
}
void Processor::op_LD(Register destination, uint16_t source)
{
	SetRegister(destination, _memoryBus->Read(source));
}

// TODO: ADDRESSING MODES, OPERATIONS