#include "Processor.hpp"

void Processor::Write(ProcessorRegisters reg, std::uint16_t value)
{
	switch (reg)
	{
	case ProcessorRegisters::AF:
		_registerAF = value;
		break;
	case ProcessorRegisters::BC:
		_registerBC = value;
		break;
	case ProcessorRegisters::DE:
		_registerDE = value;
		break;
	case ProcessorRegisters::HL:
		_registerHL = value;
		break;
	case ProcessorRegisters::SP:
		_registerSP = value;
		break;
	case ProcessorRegisters::PC:
		_registerPC = value;
		break;
	}
}
void Processor::WriteHi(ProcessorRegisters reg, std::uint8_t value)
{
	switch (reg)
	{
	case ProcessorRegisters::AF:
		_registerAF = (_registerAF & 0xFF00) | (value << 8);
		break;
	case ProcessorRegisters::BC:
		_registerBC = (_registerBC & 0xFF00) | (value << 8);
		break;
	case ProcessorRegisters::DE:
		_registerDE = (_registerDE & 0xFF00) | (value << 8);
		break;
	case ProcessorRegisters::HL:
		_registerHL = (_registerHL & 0xFF00) | (value << 8);
		break;
	case ProcessorRegisters::SP:
		_registerSP = (_registerSP & 0xFF00) | (value << 8);
		break;
	case ProcessorRegisters::PC:
		_registerPC = (_registerPC & 0xFF00) | (value << 8);
		break;
	}
}
void Processor::WriteLo(ProcessorRegisters reg, std::uint8_t value)
{
	switch (reg)
	{
	case ProcessorRegisters::AF:
		_registerAF = (_registerAF & 0x00FF) | value << 8;
		break;
	case ProcessorRegisters::BC:
		_registerBC = (_registerBC & 0x00FF) | value << 8;
		break;
	case ProcessorRegisters::DE:
		_registerDE = (_registerDE & 0x00FF) | value << 8;
		break;
	case ProcessorRegisters::HL:
		_registerHL = (_registerHL & 0x00FF) | value << 8;
		break;
	case ProcessorRegisters::SP:
		_registerSP = (_registerSP & 0x00FF) | value << 8;
		break;
	case ProcessorRegisters::PC:
		_registerPC = (_registerPC & 0x00FF) | value;
		break;
	}
}

std::uint16_t Processor::Read(ProcessorRegisters reg)
{
	switch (reg)
	{
	case ProcessorRegisters::AF:
		return _registerAF;
	case ProcessorRegisters::BC:
		return _registerBC;
	case ProcessorRegisters::DE:
		return _registerDE;
	case ProcessorRegisters::HL:
		return _registerHL;
	case ProcessorRegisters::SP:
		return _registerSP;
	case ProcessorRegisters::PC:
		return _registerPC;
	}
}
std::uint8_t Processor::ReadHi(ProcessorRegisters reg)
{
	switch (reg)
	{
	case ProcessorRegisters::AF:
		return (_registerAF & 0xFF00) >> 8;
	case ProcessorRegisters::BC:
		return (_registerBC & 0xFF00) >> 8;
	case ProcessorRegisters::DE:
		return (_registerDE & 0xFF00) >> 8;
	case ProcessorRegisters::HL:
		return (_registerHL & 0xFF00) >> 8;
	case ProcessorRegisters::SP:
		return (_registerSP & 0xFF00) >> 8;
	case ProcessorRegisters::PC:
		return (_registerPC & 0xFF00) >> 8;
	}
}
std::uint8_t Processor::ReadLo(ProcessorRegisters reg)
{
	switch (reg)
	{
	case ProcessorRegisters::AF:
		return (_registerAF & 0x00FF);
	case ProcessorRegisters::BC:
		return (_registerBC & 0x00FF);
	case ProcessorRegisters::DE:
		return (_registerDE & 0x00FF);
	case ProcessorRegisters::HL:
		return (_registerHL & 0x00FF);
	case ProcessorRegisters::SP:
		return (_registerSP & 0x00FF);
	case ProcessorRegisters::PC:
		return (_registerPC & 0x00FF);
	}
}