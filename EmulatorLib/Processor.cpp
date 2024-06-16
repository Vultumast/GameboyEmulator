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

void Processor::StackPush(uint16_t value)
{
	_memoryBus->Write(sp--, (value & 0xFF00) >> 8);
	_memoryBus->Write(sp--, (value & 0x00FF));
}

uint16_t Processor::StackPop()
{
	uint16_t returnValue = (uint16_t)(_memoryBus->Read(++sp));

	returnValue |= _memoryBus->Read(++sp) << 8;

	return returnValue;
}

void Processor::ResetVector(uint16_t address)
{
	StackPush(pc);
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

void Processor::PulseClock()
{
	_cycleCount = (_cycleCount + 1) % 0xFF;

	if (Halted)
		_remainingCycles = 0;

	// Cycle timer finished?
	if (IsInstructionCompleted())
	{
		Interrupt reqInterrupts = _memoryBus->GetInterrupts();

		// Service all pending interrupts first
		if (InterruptMasterEnable && (_memoryBus->Read(HardwareRegister::IE) != 0 && reqInterrupts != 0))
		{
			for (uint8_t i = 0; i <= Interrupt::JOYPAD; i++)
			{
				if ((reqInterrupts & i) == 0)
					continue;

				serviceInterrupt((Interrupt)i);
				break;
			}
		}
		else
		{
			// Normal Execution

			OpCodeInfo& info = OpCodeInfo::OpCodes[fetch()];

			if (info.GetOpCode() == OpCode::PREFIX)
			{
				info = OpCodeInfo::OpCodesCB[fetch()];
			}

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
			if (info.GetOpCode() == OpCode::JR || info.GetOpCode() == OpCode::JP || info.GetOpCode() == OpCode::CALL)
			{
				data = 1;

				// LHS is our conditional
				if (info.GetLeftHandOperand() >= OperandType::FlagCarry)
					data = GetOperand(info.GetLeftHandOperand());
			}

			_remainingCycles = info.GetCycleLengthMin();

			//std::stringstream sstream;
			//sstream << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(info.GetHexCode());
			//std::cout << std::dec << "executing OpCode: " << sstream.str() << std::endl;
			func(*this, info.GetLeftHandOperand(), data, GetOperand(info.GetRightHandOperand()));
		}
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
		a = (value >> 8) & 0xFF;
		f = value & 0xFF;
		break;
	case Register::BC:
		b = (value >> 8) & 0xFF;
		c = value & 0xFF;
		break;
	case Register::DE:
		d = (value >> 8) & 0xFF;
		e = value & 0xFF;
		break;
	case Register::HL:
		h = (value >> 8) & 0xFF;
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
	uint16_t addr = 0;

	uint16_t hl = 0;
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
		hl = GetRegister(Register::HL);
		data = _memoryBus->Read(hl);

		SetRegister(Register::HL, hl + 1);
		break;
	case OperandType::DecrementHL:
		hl = GetRegister(Register::HL);
		data = _memoryBus->Read(hl);
		SetRegister(Register::HL, hl - 1);
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
		data = fetch();
		data |= (fetch() << 8);
		break;
	case OperandType::AddressUINT16:
		addr = fetch();
		addr |= (fetch() << 8);
		data = _memoryBus->Read(addr);
		break;
	case OperandType::DataUINT8:
		data = fetch();
		break;
	case OperandType::AddressUINT8:
		data = _memoryBus->Read(0xFF00 + fetch());
		break;
	case OperandType::DataINT8:
		data = fetch();
		data = pc + static_cast<int8_t>(data & 0xFF);
		break;

	case OperandType::FlagCarry:
		data = GetFlag(Processor::FLAGS::C);
		break;
	case OperandType::FlagHalfCarry:
		data = GetFlag(Processor::FLAGS::H);
		break;
	case OperandType::FlagNegative:
		data = GetFlag(Processor::FLAGS::N);
		break;
	case OperandType::FlagZero:
		data = GetFlag(Processor::FLAGS::Z);
		break;

	case OperandType::FlagNotCarry:
		data = !GetFlag(Processor::FLAGS::C);
		break;
	case OperandType::FlagNotHalfCarry:
		data = !GetFlag(Processor::FLAGS::H);
		break;
	case OperandType::FlagNotNegative:
		data = !GetFlag(Processor::FLAGS::N);
		break;
	case OperandType::FlagNotZero:
		data = !GetFlag(Processor::FLAGS::Z);
		break;
	}

	return data;
}

#pragma region Private Methods
uint8_t Processor::fetch()
{
	uint8_t value = _memoryBus->Read(pc);
	pc = (pc + 1) & 0xFFFF;
	return value;
}
void Processor::serviceInterrupt(Interrupt interrupt)
{
	std::cout << "SERVICING INTERRUPT: ";
	uint8_t handler = 0x40;

	switch (interrupt)
	{
	case VBLANK:
		handler = 0x40;
		std::cout << "VBLANK";
		break;
	case LCD:
		handler = 0x48;
		std::cout << "LCD";
		break;
	case TIMER:
		handler = 0x50;
		std::cout << "TIMER";
		break;
	case SERIAL:
		handler = 0x58;
		std::cout << "SERIAL";
		break;
	case JOYPAD:
		handler = 0x60;
		std::cout << "JOYPAD";
		break;
	}

	std::cout << std::endl;

	// di; call $00hh (copied from Instructions.cpp)
	// Disable so we can actually run interrupt code at the reset vector
	InterruptMasterEnable = false;
	
	ResetVector(handler);

	std::stringstream sstream;
	sstream << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(handler);
	std::cout << std::dec << "RESET VECTOR HIT: " << sstream.str() << std::endl;

	_remainingCycles = 20;

	_memoryBus->Write(HardwareRegister::IF, (uint8_t)_memoryBus->Read(HardwareRegister::IF) & ~(1 << (interrupt - 1))); // Reset Serviced Interrupt

}
#pragma endregion