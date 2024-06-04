#include "Processor.hpp"
#include "Constants.hpp"
#include "MemoryBus.hpp"



Processor::Processor(MemoryBus* memoryBus)
{
	_memoryBus = memoryBus;
}

uint8_t Processor::read(uint16_t addr)
{
	uint8_t value = _memoryBus->Read(addr);
	return value;
}

void Processor::write(uint16_t addr, uint8_t value)
{
	_memoryBus->Write(addr, value);
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

void Processor::PulseClock()
{
	_cycleCount = (_cycleCount + 1) % 0xFF;
	_remainingCycles--;

	// Cycle timer finished?
	if (IsInstructionCompleted())
	{
		OpCodeInfo& info = OpCodes[fetch()];

		std::function<void(Processor&, uint16_t, uint16_t)>& func = Instructions[info.GetHexCode()];

		func(*this, (uint16_t)info.GetLeftHandOperand(), GetOperand(info.GetRightHandOperand()));
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
uint16_t Processor::GetRegister(Register source) const
{
	switch (source)
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

uint16_t Processor::GetSourceValue(Register source, bool direct)
{
	if (direct)
		return GetRegister(source);
	else
		return _memoryBus->Read(GetRegister(source));
}
uint16_t Processor::GetSourceValue(uint16_t source, bool direct)
{
	if (direct)
		return _memoryBus->Read(source);
	else
		return _memoryBus->Read(_memoryBus->Read(source));
}

void Processor::SetDestinationValue(Register destination, uint16_t source, bool direct)
{
	if (direct)
		SetRegister(destination, source);
	else
		_memoryBus->Write(GetRegister(destination), source);
}
void Processor::SetDestinationValue(uint16_t destination, uint16_t source, bool direct)
{
	if (direct)
		_memoryBus->Write(destination, source);
	else
		_memoryBus->Write(_memoryBus->Read(destination), source);
}

uint16_t Processor::GetOperand(OperandType operand)
{
	uint16_t data = 0;

	switch (operand)
	{
	case OperandType::Acculumator:
		data = a;
		break;
	case OperandType::RegisterB:
		data = b;
		break;
	case OperandType::RegisterC:
		data = c;
		break;
	case OperandType::RegisterD:
		data = d;
		break;
	case OperandType::RegisterE:
		data = e;
		break;
	case OperandType::RegisterH:
		data = h;
		break;
	case OperandType::RegisterL:
		data = l;
		break;
	case OperandType::RegisterAF:
		data = (f | a << 8);
		break;
	case OperandType::RegisterBC:
		data = (c | b << 8);
		break;
	case OperandType::RegisterDE:
		data = (e | d << 8);
		break;
	case OperandType::RegisterHL:
		data = (l | h << 8);
		break;
	case OperandType::Stackpointer:
		data = sp;
		break;
	case OperandType::ProgramCounter:
		data = pc;
		break;
	case OperandType::DataUINT16:
		data = fetch();
		data |= (fetch() << 8);
		break;
	case OperandType::DataUINT8:
		data = fetch();
		break;
	}

	return data;
}

uint8_t Processor::fetch()
{
	uint8_t value = _memoryBus->Read(pc);
	pc = (pc + 1) & 0xFFFF;
	return value;
}
