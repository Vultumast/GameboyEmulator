#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "Constants.hpp"
#include "MemoryBus.hpp"
#include "OpCodeInfo.hpp"
#include "InstructionArguments.hpp"

#include "Processor.hpp"


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

	Halted = false;
	InterruptMasterEnable = false;
}

void Processor::PulseClock()
{
	static uint8_t& regInterruptEnable = *_memoryBus->Get(HardwareRegister::IE);
	static Interrupt& reqInterrupts = reinterpret_cast<Interrupt&>(*_memoryBus->Get(HardwareRegister::IF));
	static OpCodeInfo* info = nullptr;
	static InstructionArguments args = { *this, *_memoryBus, *info, OperandType::None, OperandType::None, 0, 0 };
	_cycleCount++;


	if (Stopped)
		return;

	bool interruptPending = InterruptMasterEnable && (reqInterrupts != 0 && regInterruptEnable != 0);
	if (Halted)
	{
		_remainingCycles = 0;
		if (interruptPending)
			Halted = false;
		else
			return;
	}

	// Cycle timer finished?
	if (_remainingCycles == 0)
	{
		// Service all pending interrupts first
		if (interruptPending)
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

			

			info = OpCodeInfo::OpCodes + fetch();

			std::function<void(InstructionArguments&)>* func = Instructions + info->GetHexCode();


			if (info->GetOpCode() == OpCode::PREFIX)
			{
				info = OpCodeInfo::OpCodesCB + fetch();
				func = InstructionsCB + info->GetHexCode();
			}

			args._opcodeInfo = info;
			args._lhs = info->GetLeftHandOperand();
			args._rhs = info->GetRightHandOperand();
			args._lhsValue = GetOperand(args._lhs);
			args._rhsValue = GetOperand(args._rhs);

			_remainingCycles = info->GetCycleLengthMin();

			//std::stringstream sstream;
			//sstream << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(info.GetHexCode());
			//std::cout << std::dec << "executing OpCode: " << sstream.str() << std::endl;
			(*func)(args);
		}
	}
	else
		_remainingCycles--;
	
}	
void Processor::ConsumeInstruction()
{
	_cycleCount = (_cycleCount + _remainingCycles) % 0xFF;
	_remainingCycles = 0;
	PulseClock();
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

void Processor::SetRegister8Bit(Registers8Bit destination, uint8_t value)
{
	switch (destination)
	{
	case Registers8Bit::B:
		b = value;
		break;
	case Registers8Bit::C:
		c = value;
		break;
	case Registers8Bit::D:
		d = value;
		break;
	case Registers8Bit::E:
		e = value;
		break;
	case Registers8Bit::H:
		h = value;
		break;
	case Registers8Bit::L:
		l = value;
		break;
	case Registers8Bit::HL_Indirect:
		_memoryBus->Write(static_cast<uint16_t>((h << 8) | (l)), value);
		break;
	case Registers8Bit::A:
		a = value;
		break;
	}
}
uint8_t Processor::GetRegister8Bit(Registers8Bit source) const
{
	switch (source)
	{
	case Registers8Bit::B:
		return b;
	case Registers8Bit::C:
		return c;
	case Registers8Bit::D:
		return d;
	case Registers8Bit::E:
		return e;
	case Registers8Bit::H:
		return h;
	case Registers8Bit::L:
		return l;
	case Registers8Bit::HL_Indirect:
		return _memoryBus->Read(static_cast<uint16_t>((h << 8) | (l)));
		break;
	case Registers8Bit::A:
		return a;
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

	uint16_t hl = h;
	hl <<= 8;
	hl |= l;


	/*if ((static_cast<uint8_t>(operand) - 1) <= static_cast<uint8_t>(Register::PC))
	{
		return GetRegister(static_cast<Register>(static_cast<uint8_t>(operand) - 1));
	}*/

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
		data = (static_cast<uint16_t>(a << 8) | f);
		break;
	case OperandType::RegisterBC:
		data = (static_cast<uint16_t>(b << 8) | c);
		break;
	case OperandType::RegisterDE:
		data = (static_cast<uint16_t>(d << 8) | e);
		break;
	case OperandType::RegisterHL:
		data = (static_cast<uint16_t>(h << 8) | l);
		break;
	case OperandType::Stackpointer:
		data = sp;
		break;
	case OperandType::ProgramCounter:
		data = pc;
		break;
	case OperandType::IncrementHL:
		data = _memoryBus->Read(hl);
		SetRegister(Register::HL, hl + 1);
		break;
	case OperandType::DecrementHL:
		data = _memoryBus->Read(hl);
		SetRegister(Register::HL, hl - 1);
		break;

	case OperandType::RegisterCIndirect:
		data = _memoryBus->Read(0xFF00 + c);
		break;
	case OperandType::RegisterBCIndirect:
		data = _memoryBus->Read((static_cast<uint16_t>(b << 8) | c));
		break;
	case OperandType::RegisterDEIndirect:
		data = _memoryBus->Read((static_cast<uint16_t>(d << 8) | e));
		break;
	case OperandType::RegisterHLIndirect:
		data = _memoryBus->Read((static_cast<uint16_t>(h << 8) | l));
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
	case OperandType::AddressUINT8:
		data = fetch();
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
uint16_t Processor::fetchWord()
{
	uint16_t value = fetch();
	value |= static_cast<uint16_t>(fetch()) << 8;
	return value;
}

void Processor::serviceInterrupt(Interrupt interrupt)
{
	// std::cout << "SERVICING INTERRUPT: ";
	uint8_t handler = 0x40;

	switch (interrupt)
	{
	case VBLANK:
		handler = 0x40;
		// std::cout << "VBLANK";
		break;
	case LCD:
		handler = 0x48;
		// std::cout << "LCD";
		break;
	case TIMER:
		handler = 0x50;
		// std::cout << "TIMER";
		break;
	case SERIAL:
		handler = 0x58;
		// std::cout << "SERIAL";
		break;
	case JOYPAD:
		handler = 0x60;
		// std::cout << "JOYPAD";
		break;
	}

	// std::cout << std::endl;

	// di; call $00hh (copied from Instructions.cpp)
	// Disable so we can actually run interrupt code at the reset vector
	InterruptMasterEnable = false;
	
	ResetVector(handler);

	/* std::stringstream sstream;
	sstream << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(handler);
	std::cout << std::dec << "RESET VECTOR HIT: " << sstream.str() << std::endl;
	*/
	_remainingCycles = 20;

	_memoryBus->Write(HardwareRegister::IF, (uint8_t)_memoryBus->Read(HardwareRegister::IF) & ~(1 << (interrupt - 1))); // Reset Serviced Interrupt

}

void Processor::decodeOpcode()
{
	uint8_t opcode = fetch();

	uint8_t opcodeCateogry = (opcode & 0b11000000) >> 6;
	switch (opcodeCateogry)
	{
	case 0:
		decodeOpCodeGroup0(opcode);
		break;
	case 1: // 8 bit loading
		decodeOpCodeGroup1(opcode);
		break;
	case 2:
		decodeOpCodeGroup2(opcode);
		break;
	case 3:
		decodeOpCodeGroup3(opcode);
		break;
	}
}

void Processor::decodeOpCodeGroup0(uint8_t opcode)
{
	uint8_t y = (opcode & 0b00111000) >> 3;
	uint8_t z = (opcode & 0b00000111);

	switch (z)
	{
	case 0: // Relative Jumps and Misc Ops
		decodeOpCodeSubgroup00(opcode);
		break;
	case 1: // 16-bit load immediate / add
		decodeOpCodeSubgroup01(opcode);
		break;
	case 2: // 16-bit load immediate / add
		decodeOpCodeSubgroup02(opcode);
		break;
	case 3: // Indirect loading
		decodeOpCodeSubgroup03(opcode);
		break;
	case 4: // 8-bit INC
		decodeOpCodeSubgroup04(opcode);
		break;
	case 5: // 8-bit DEC
		decodeOpCodeSubgroup05(opcode);
		break;
	case 6: // 8-bit load immediate
		decodeOpCodeSubgroup06(opcode);
		break;
	case 7: // Misc Accumulator/Flag operations
		decodeOpCodeSubgroup07(opcode);
		break;
	}

}
void Processor::decodeOpCodeGroup1(uint8_t opcode)
{
	_previousOpCode = OpCode::LD;
	_remainingCycles = 4;
	uint8_t dstReg = (opcode & 0b00111000) >> 3;
	uint8_t srcReg = (opcode & 0b00000111);

	uint8_t data = 0;

	if (dstReg == Registers8Bit::HL_Indirect && srcReg == Registers8Bit::HL_Indirect) // LD (HL), (HL) == HALT
	{
		Halted = true;
		return;
	}

	SetRegister8Bit(static_cast<Registers8Bit>(dstReg), GetRegister8Bit(static_cast<Registers8Bit>(srcReg)));
}
void Processor::decodeOpCodeGroup2(uint8_t opcode)
{
	uint8_t operation = (opcode & 0b00111000) >> 3;
	uint8_t srcReg =    (opcode & 0b00000111) >> 3;

	_remainingCycles = 4;

	if (srcReg == Registers8Bit::HL_Indirect)
		_remainingCycles = 8;

	uint8_t temp = 0;
	uint8_t src = GetRegister8Bit(static_cast<Registers8Bit>(srcReg));

	f = 0; // Clear flags

	switch (operation)
	{
	case ArithmeticLogicOperations::ADD_A:
		_previousOpCode = OpCode::ADD;
		temp = a;
		a = src + a;
		SetFlag(FLAGS::Z, a == 0);
		SetFlag(FLAGS::N, false);
		SetFlag(FLAGS::H, (((temp & 0xF) + (src & 0xF)) & 0x10) == 0x10);
		SetFlag(FLAGS::C, (static_cast<uint32_t>(temp) + static_cast<uint32_t>(src)) > 0xFFFF);
		break;
	case ArithmeticLogicOperations::ADC_A:
		_previousOpCode = OpCode::ADC;
		temp = a;
		a = src + a + GetFlag(FLAGS::C);
		SetFlag(FLAGS::Z, a == 0);
		SetFlag(FLAGS::N, false);
		SetFlag(FLAGS::H, (((temp & 0xF) + (src & 0xF) + (GetFlag(FLAGS::C) & 0x0F)) & 0x10) == 0x10);
		SetFlag(FLAGS::C, (static_cast<uint32_t>(temp) + static_cast<uint32_t>(src) + static_cast<uint32_t>(GetFlag(FLAGS::C))) > 0xFFFF);
		break;
	case ArithmeticLogicOperations::SUB:
		_previousOpCode = OpCode::SUB;
		temp = a;
		a = a - src;
		SetFlag(FLAGS::Z, a == 0);
		SetFlag(FLAGS::N, true);
		SetFlag(FLAGS::H, (((temp & 0xF) - (src & 0xF)) < 0x10) && a >= 0x10);
		SetFlag(FLAGS::C, temp == src);
		break;
	case ArithmeticLogicOperations::SBC_A:
		_previousOpCode = OpCode::SBC;
		temp = a;
		a = a - src - GetFlag(FLAGS::C);
		SetFlag(FLAGS::Z, a == 0);
		SetFlag(FLAGS::N, true);
		SetFlag(FLAGS::H, (((temp & 0xF) - (src & 0xF) - (GetFlag(FLAGS::C) & 0x0F)) < 0x10) && a >= 0x10);
		SetFlag(FLAGS::C, temp == src);
		break;
	case ArithmeticLogicOperations::AND:
		_previousOpCode = OpCode::AND;
		a &= src;
		SetFlag(FLAGS::Z, a == 0);
		SetFlag(FLAGS::N, false);
		SetFlag(FLAGS::H, true);
		SetFlag(FLAGS::C, false);
		break;
	case ArithmeticLogicOperations::XOR:
		_previousOpCode = OpCode::XOR;
		a ^= src;
		SetFlag(FLAGS::Z, a == 0);
		SetFlag(FLAGS::N, false);
		SetFlag(FLAGS::H, false);
		SetFlag(FLAGS::C, false);
		break;
	case ArithmeticLogicOperations::OR:
		_previousOpCode = OpCode::OR;
		a |= src;
		SetFlag(FLAGS::Z, a == 0);
		SetFlag(FLAGS::N, false);
		SetFlag(FLAGS::H, false);
		SetFlag(FLAGS::C, false);
		break;
	case ArithmeticLogicOperations::CP:
		_previousOpCode = OpCode::CP;
		SetFlag(FLAGS::Z, a - src == 0);
		SetFlag(FLAGS::N, true);
		SetFlag(FLAGS::H, a >= 0x10 && ((a - src) < 0x10));
		SetFlag(FLAGS::C, src > a);
		break;
	}
}
void Processor::decodeOpCodeGroup3(uint8_t opcode)
{
	uint8_t y = (opcode & 0b00111000) >> 3;
	uint8_t z = (opcode & 0b00000111);

	switch (z)
	{
	case 0:
		decodeOpCodeSubgroup30(opcode);
		break;
	case 1:
		decodeOpCodeSubgroup31(opcode);
		break;
	case 2:
		decodeOpCodeSubgroup32(opcode);
		break;
	case 3:
		decodeOpCodeSubgroup33(opcode);
		break;
	case 4:
		decodeOpCodeSubgroup34(opcode);
		break;
	case 5:
		decodeOpCodeSubgroup35(opcode);
		break;
	case 6:
		decodeOpCodeSubgroup36(opcode);
		break;
	case 7:
		decodeOpCodeSubgroup37(opcode);
		break;
	}
}


void Processor::decodeOpCodeSubgroup00(uint8_t opcode)
{
	uint8_t y = (opcode & 0b00111000) >> 3;
	switch (y)
	{
	case 0:
		_previousOpCode = OpCode::NOP;
		_remainingCycles = 4;
		break;
	case 1:
		_previousOpCode = OpCode::LD;
		sp = fetchWord();
		_remainingCycles = 20;
		break;
	case 2:
		_previousOpCode = OpCode::STOP;
		_remainingCycles = 4;
		pc++; // It doesn't matter what byte comes after stop
		break;
	case 3:
		_previousOpCode = OpCode::JR;
		pc += (int8_t)fetch();
		_remainingCycles = 12;
		break;
	default:
		_previousOpCode = OpCode::JR;
		switch (y - 4) // Condition
		{
		case Conditionals::NZ:
			_remainingCycles = (f & FLAGS::Z) == 0 ? 12 : 8;
			break;
		case Conditionals::Z:
			_remainingCycles = (f & FLAGS::Z) != 0 ? 12 : 8;
			break;
		case Conditionals::NC:
			_remainingCycles = (f & FLAGS::C) == 0 ? 12 : 8;
			break;
		case Conditionals::C:
			_remainingCycles = (f & FLAGS::C) != 0 ? 12 : 8;
			break;
		}

		if (_remainingCycles == 12) // Did we take the branch?
			pc += (int8_t)fetch();
		else
			pc++; // Skip the next byte
		break;
	}
}
void Processor::decodeOpCodeSubgroup01(uint8_t opcode)
{
	uint8_t p = (opcode & 0b00110000) >> 4;
	bool q =    (opcode & 0b00001000) >> 3;

	if (q)
	{
		_previousOpCode = OpCode::LD;
		_remainingCycles = 12;

		switch (p)
		{
		case Registers16BitA::BC:
			c = fetch();
			b = fetch();
			break;
		case Registers16BitA::DE:
			e = fetch();
			d = fetch();
			break;
		case Registers16BitA::HL:
			l = fetch();
			h = fetch();
			break;
		case Registers16BitA::SP:
			sp = fetchWord();
			break;
		}
	}
	else
	{
		uint16_t hl = (static_cast<uint16_t>(h) << 8) | l;
		uint16_t src = 0;
		_remainingCycles = 8;

		switch (p)
		{
		case Registers16BitA::BC:
			src = (static_cast<uint16_t>(b) << 8) | c;
			break;
		case Registers16BitA::DE:
			src = (static_cast<uint16_t>(d) << 8) | e;
			break;
		case Registers16BitA::HL:
			src = (static_cast<uint16_t>(h) << 8) | l;
			break;
		case Registers16BitA::SP:
			src = sp;;
			break;
		}

		SetFlag(FLAGS::N, false);
		SetFlag(FLAGS::H, ((hl + src) & 0x1000) == 0x1000);
		SetFlag(FLAGS::C, (hl + src) < hl); // We could only be less if we wrapped around
		_previousOpCode = OpCode::ADD;
	}
}
void Processor::decodeOpCodeSubgroup02(uint8_t opcode)
{
	uint8_t p = (opcode & 0b00110000) >> 4;
	bool flip = (opcode & 0b00001000);

	uint16_t address = 0;

	_remainingCycles = 8;
	_previousOpCode = OpCode::LD;

	switch (p)
	{
	case 0:
		address = (static_cast<uint16_t>(b) << 8) | c;
		break;
	case 1:
		address = (static_cast<uint16_t>(d) << 8) | e;
		break;
	case 2:
		address = (static_cast<uint16_t>(h) << 8) | l;
		address++;
		h = (address & 0xFF00) >> 8;
		l = (address & 0x00FF);
		break;	
	case 3:
		address = (static_cast<uint16_t>(h) << 8) | l;
		address--;
		h = (address & 0xFF00) >> 8;
		l = (address & 0x00FF);
		break;
	}

	if (flip)
		_memoryBus->Write(address, a);
	else
		a = _memoryBus->Read(address);
}
void Processor::decodeOpCodeSubgroup03(uint8_t opcode)
{
	uint8_t reg = (opcode & 0b00110000) >> 4;
	bool opType = (opcode & 0b00001000);

	uint16_t src = 0;

	switch (reg)
	{
	case BC:
		src = (static_cast<uint16_t>(b) << 8) | c;
		break;
	case DE:
		src = (static_cast<uint16_t>(d) << 8) | e;
		break;
	case HL:
		src = (static_cast<uint16_t>(h) << 8) | l;
		break;
	case SP:
		src = sp;
		break;
	}

	_remainingCycles = 8;

	if (opType)
	{
		_previousOpCode = OpCode::INC;
		src++;
	}
	else
	{
		_previousOpCode = OpCode::DEC;
		src--;
	}

	switch (reg)
	{
	case BC:
		b = (src & 0xFF00) >> 8;
		c = (src & 0x00FF);
		break;
	case DE:
		d = (src & 0xFF00) >> 8;
		e = (src & 0x00FF);
		break;
	case HL:
		h = (src & 0xFF00) >> 8;
		l = (src & 0x00FF);
		break;
	case SP:
		sp = src;
		break;
	}
}
void Processor::decodeOpCodeSubgroup04(uint8_t opcode)
{
	_remainingCycles = 4;
	_previousOpCode = OpCode::INC;

	uint8_t reg = (opcode & 0b00111000) >> 4;

	uint8_t src = 0;
	uint16_t hl = (static_cast<uint16_t>(h) << 8) | l;
	switch (reg)
	{
	case Registers8Bit::B:
		src = b;
		b++;
		break;
	case Registers8Bit::C:
		src = c;
		c++;
		break;
	case Registers8Bit::D:
		src = d;
		d++;
		break;
	case Registers8Bit::E:
		src = e;
		e++;
		break;
	case Registers8Bit::H:
		src = h;
		h++;
		break;
	case Registers8Bit::L:
		src = l;
		l++;
		break;
	case Registers8Bit::HL_Indirect:
		_remainingCycles = 12;
		src = _memoryBus->Read(hl);
		_memoryBus->Write(hl, src + 1);
		break;
	case Registers8Bit::A:
		src = a;
		a++;
		break;
	}

	SetFlag(FLAGS::Z, src == 0xFF);
	SetFlag(FLAGS::N, false);
	SetFlag(FLAGS::H, (((1 & 0xF) + (src & 0xF)) & 0x10) == 0x10));
}
void Processor::decodeOpCodeSubgroup05(uint8_t opcode)
{
	_remainingCycles = 4;
	_previousOpCode = OpCode::DEC;

	uint8_t reg = (opcode & 0b00111000) >> 4;

	uint8_t src = 0;
	uint16_t hl = (static_cast<uint16_t>(h) << 8) | l;
	switch (reg)
	{
	case Registers8Bit::B:
		src = b;
		b--;
		break;
	case Registers8Bit::C:
		src = c;
		c--;
		break;
	case Registers8Bit::D:
		src = d;
		d--;
		break;
	case Registers8Bit::E:
		src = e;
		e--;
		break;
	case Registers8Bit::H:
		src = h;
		h--;
		break;
	case Registers8Bit::L:
		src = l;
		l--;
		break;
	case Registers8Bit::HL_Indirect:
		_remainingCycles = 12;
		src = _memoryBus->Read(hl);
		_memoryBus->Write(hl, src - 1);
		break;
	case Registers8Bit::A:
		src = a;
		a--;
		break;
	}

	SetFlag(FLAGS::Z, src == 0x01);
	SetFlag(FLAGS::N, false);
	SetFlag(FLAGS::H, ((src - 1) & 0x10) == 0x10);

}
void Processor::decodeOpCodeSubgroup06(uint8_t opcode)
{
	_remainingCycles = 8;
	_previousOpCode = OpCode::LD;
	uint8_t reg = (opcode & 0b00111000) >> 4;
	uint16_t hl = (static_cast<uint16_t>(h) << 8) | l;

	switch (reg)
	{
	case Registers8Bit::B:
		b = fetch();
		break;
	case Registers8Bit::C:
		c = fetch();
		break;
	case Registers8Bit::D:
		d = fetch();
		break;
	case Registers8Bit::E:
		e = fetch();
		break;
	case Registers8Bit::H:
		h = fetch();
		break;
	case Registers8Bit::L:
		l = fetch();
		break;
	case Registers8Bit::HL_Indirect:
		_remainingCycles = 12;
		_memoryBus->Write(hl, fetch());
		break;
	case Registers8Bit::A:
		a = fetch();
		break;
	}
}
void Processor::decodeOpCodeSubgroup07(uint8_t opcode)
{
	uint8_t operation = (opcode & 0b00111000) >> 3;

	_remainingCycles = 4;

	uint8_t temp = 0;

	switch (operation)
	{
	case 0:
		_previousOpCode = OpCode::RLCA;
		if ((a & 0x80) == 0x80)
		{
			a <<= 1;
			a |= 0b1;
			f = FLAGS::C;
		}
		else
		{
			a <<= 1;
			f = 0x0;
		}
		break;
	case 1:
		_previousOpCode = OpCode::RRCA;
		if ((a & 0x1) == 0x1)
		{
			a >>= 1;
			a |= 0x80;
			f = FLAGS::C;
		}
		else
		{
			a >>= 1;
			f = 0x0;
		}
		break;
	case 2:
		_previousOpCode = OpCode::RLA;
		temp = f;
		f = ((a & 0x80) == 0x80) ? FLAGS::C : 0;
		a <<= 1;
		a |= ((f & FLAGS::C) == FLAGS::C);
		break;
	case 3:
		_previousOpCode = OpCode::RRA;
		temp = f;
		f = ((a & 0x1) == 0x1) ? FLAGS::C : 0;
		a >>= 1;
		a |= (((f & FLAGS::C) == FLAGS::C) << 7);
		break;
	case 4:
		_previousOpCode = OpCode::DAA;

		if ((f & FLAGS::N) == FLAGS::N)
		{
			if ((a & 0xF0) > 0x99 || ((f & FLAGS::C) == FLAGS::C))
			{
				a += 0x60;
				SetFlag(FLAGS::C, true);
			}
			if ((a & 0x0F) > 0x09 || ((f & FLAGS::H) == FLAGS::H))
				a += 0x06;
		}
		else
		{
			if ((f & FLAGS::C) == FLAGS::C)
				a -= 0x60;
			if ((f & FLAGS::H) == FLAGS::H)
				a -= 0x6;
		}
		SetFlag(FLAGS::Z, a == 0);
		SetFlag(FLAGS::H, false);
		break;
	case 5:
		_previousOpCode = OpCode::CPL;
		a = ~a;
		SetFlag(FLAGS::N, true);
		SetFlag(FLAGS::H, true);
		break;
	case 6:
		_previousOpCode = OpCode::SCF;
		SetFlag(FLAGS::N, false);
		SetFlag(FLAGS::H, false);
		SetFlag(FLAGS::C, true);
		break;
	case 7:
		_previousOpCode = OpCode::CCF;
		SetFlag(FLAGS::N, false);
		SetFlag(FLAGS::H, false);
		SetFlag(FLAGS::C, !GetFlag(FLAGS::C));
		break;
	}
}


void Processor::decodeOpCodeSubgroup30(uint8_t opcode)
{
	uint8_t y = (opcode & 0b00111000) >> 3;
	switch (y)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		_previousOpCode = OpCode::RET;

		break;
	case 4:
		_previousOpCode = OpCode::LDH;

		break;
	case 5:
		_previousOpCode = OpCode::ADD;

		break;
	case 6:
		break;
	case 7:
		_previousOpCode = OpCode::LD;

		break;

	}
}
void Processor::decodeOpCodeSubgroup31(uint8_t opcode)
{

}
void Processor::decodeOpCodeSubgroup32(uint8_t opcode)
{

}
void Processor::decodeOpCodeSubgroup33(uint8_t opcode)
{

}
void Processor::decodeOpCodeSubgroup34(uint8_t opcode)
{

}
void Processor::decodeOpCodeSubgroup35(uint8_t opcode)
{

}
void Processor::decodeOpCodeSubgroup36(uint8_t opcode)
{

}
void Processor::decodeOpCodeSubgroup37(uint8_t opcode)
{

}
#pragma endregion