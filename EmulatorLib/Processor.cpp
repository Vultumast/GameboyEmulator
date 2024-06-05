#include "Processor.hpp"
#include "Constants.hpp"
#include "MemoryBus.hpp"
#include "OpCodeInfo.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

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

void Processor::Push(uint16_t value)
{
	sp -= 2;
	_memoryBus->Write(sp, value & 0xFF);
	_memoryBus->Write(sp, (value & 0x00FF) >> 8);
}

void Processor::ResetVector(uint16_t address)
{
	Push(pc);
	pc = address;
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

	// Cycle timer finished?
	if (IsInstructionCompleted())
	{
		OpCodeInfo& info = OpCodeInfo::OpCodes[fetch()];

		std::function<void(Processor&, OperandType, uint16_t, uint16_t)>& func = Instructions[info.GetHexCode()];

		uint16_t data = 0;
		switch (info.GetLeftHandOperand())
		{
		case OperandType::DataUINT8:
		case OperandType::AddressUINT8:
			data = fetch();
			break;
		case OperandType::DataUINT16:
		case OperandType::AddressUINT16:
			data = fetch();
			data |= (fetch() << 8);
			break;
		}

		// Special case for conditionals
		if (info.GetOpCode() == OpCode::JR || info.GetOpCode() == OpCode::JP)
		{
			data = 1;

			if (info.GetLeftHandOperand() >= OperandType::FlagCarry)
				data = GetOperand(info.GetLeftHandOperand());
		}

		// Special case for RST instructions
		if ((info.GetHexCode() & 0xC7) == 0xC7)
		{
			uint8_t op = info.GetHexCode();
			data = ((op & 0xF0) - 0xC0) + (op & 0x08);
		}

		std::stringstream sstream;
		sstream << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(info.GetHexCode());
		std::cout << std::dec << "executing OpCode: " << sstream.str() << std::endl;
		func(*this, info.GetLeftHandOperand(), data, GetOperand(info.GetRightHandOperand()));
	}
	else
		_remainingCycles--;
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

bool Processor::GetFlag(FLAGS flag) const
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
	case OperandType::RegisterB:
	case OperandType::RegisterC:
	case OperandType::RegisterD:
	case OperandType::RegisterE:
	case OperandType::RegisterH:
	case OperandType::RegisterL:
	case OperandType::RegisterAF:
	case OperandType::RegisterBC:
	case OperandType::RegisterDE:
	case OperandType::RegisterHL:
	case OperandType::Stackpointer:
	case OperandType::ProgramCounter:
		data = GetRegister((Register)(((uint16_t)operand) - 1));
		break;
	case OperandType::IncrementHL:
		data = (GetRegister(Register::HL) + 1) & 0xFFFF;
		SetRegister(Register::HL, data);
		break;
	case OperandType::DecrementHL:
		data = (GetRegister(Register::HL) - 1) & 0xFFFF;
		SetRegister(Register::HL, data);
		break;

	case OperandType::RegisterCIndirect:
		data = _memoryBus->Read(0xFF00 + GetRegister(Register::C));
		break;
	case OperandType::RegisterBCIndirect:
		data = _memoryBus->Read(GetRegister(Register::BC));
		break;
	case OperandType::RegisterDEIndirect:
		data = _memoryBus->Read(GetRegister(Register::DE));
		break;
	case OperandType::RegisterHLIndirect:
		data = _memoryBus->Read(GetRegister(Register::HL));
		break;

	case OperandType::DataUINT16:
	case OperandType::AddressUINT16:
		data = fetch();
		data |= (fetch() << 8);
		break;
	case OperandType::DataUINT8:
		data = fetch();
		break;
	case OperandType::AddressUINT8:
		data = 0xFF00 | fetch();
		break;
	case OperandType::DataINT8:
		data = fetch();
		data = pc + static_cast<int8_t>(data & 0xFF);
		break;

	case OperandType::FlagCarry:
	case OperandType::FlagHalfCarry:
	case OperandType::FlagNegative:
	case OperandType::FlagZero:
		data = GetFlag((Processor::FLAGS)(((uint16_t)operand) - (uint16_t)OperandType::FlagCarry));
		break;

	case OperandType::FlagNotCarry:
	case OperandType::FlagNotHalfCarry:
	case OperandType::FlagNotNegative:
	case OperandType::FlagNotZero:
		data = !GetFlag((Processor::FLAGS)(((uint16_t)operand) - (uint16_t)OperandType::FlagCarry));
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
