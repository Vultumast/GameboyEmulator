#include "MemoryBus.hpp";
#include "ROMInfo.hpp"
#include "MapperImpl.hpp"
#include "MBC1.hpp"

#include <algorithm>
#include <iostream>

uint16_t MemoryBus::translateAddress(uint16_t address)
{
	std::uint16_t realAddress = address;
	if (!EchoRAMUsable && (realAddress >= Addr_ERAM_Start && realAddress <= Addr_ERAM_End))
		realAddress -= 0x2000;

	return realAddress;
}

MemoryBus::MemoryBus(ROMInfo* rom)
{
	_rom = rom;

	switch (rom->GetMapperType())
	{
	case MapperType::MBC1:
		_mapper = new MBC1Mapper(rom);
		break;
	}
}
MemoryBus::~MemoryBus()
{
	if (_mapper != nullptr)
		delete _mapper;
}
void MemoryBus::Randomize()
{
	for (auto i = 0; i < 0x10000; i++)
		_ram[i] = rand() % 0xFF;
}

bool MemoryBus::IsAddressMapped(const std::uint16_t& address)
{
	return true;

	if (address >= HardwareRegister::P1_JOYP) // Check IO Registers
	{
		if (address >= HardwareRegister::WAVE_RAM_START && address <= HardwareRegister::WAVE_RAM_END)
			return true;

		switch (address)
		{
		case HardwareRegister::P1_JOYP:
		case HardwareRegister::SB:
		case HardwareRegister::SC:
		case HardwareRegister::DIV:
		case HardwareRegister::TAC:
		case HardwareRegister::IF:
		case HardwareRegister::NR10:
		case HardwareRegister::NR11:
		case HardwareRegister::NR12:
		case HardwareRegister::NR13:
		case HardwareRegister::NR14:
		case HardwareRegister::NR21:
		case HardwareRegister::NR22:
		case HardwareRegister::NR23:
		case HardwareRegister::NR24:
		case HardwareRegister::NR30:
		case HardwareRegister::NR31:
		case HardwareRegister::NR32:
		case HardwareRegister::NR33:
		case HardwareRegister::NR34:
		case HardwareRegister::NR41:
		case HardwareRegister::NR42:
		case HardwareRegister::NR43:
		case HardwareRegister::NR44:
		case HardwareRegister::NR50:
		case HardwareRegister::NR51:
		case HardwareRegister::NR52:
		case HardwareRegister::LCDC:
		case HardwareRegister::STAT:
		case HardwareRegister::SCY:
		case HardwareRegister::SCX:
		case HardwareRegister::LY:
		case HardwareRegister::LYC:
		case HardwareRegister::DMA:
		case HardwareRegister::BGP:
		case HardwareRegister::OBP0:
		case HardwareRegister::OBP1:
		case HardwareRegister::WY:
		case HardwareRegister::WX:
		case HardwareRegister::KEY:
		case HardwareRegister::VBK:
		case HardwareRegister::HDMA1:
		case HardwareRegister::HDMA2:
		case HardwareRegister::HDMA3:
		case HardwareRegister::HDMA4:
		case HardwareRegister::HDMA5:
		case HardwareRegister::RP:
		case HardwareRegister::BCPS_BCPI:
		case HardwareRegister::BCPD_BGPD:
		case HardwareRegister::OCPS_OBPI:
		case HardwareRegister::OPRI:
		case HardwareRegister::SVBK:
		case HardwareRegister::PCM12:
		case HardwareRegister::PCM34:
		case HardwareRegister::IE:
			return true;
		default:
			return false;
		}
	}
	

	return true;
}

void MemoryBus::Write(const std::uint16_t& address, const std::uint8_t& value)
{
	if (!IsAddressMapped(address))
		return;

	if (address <= 0x7FFF)
	{
		if (_mapper != nullptr)
			return _mapper->Write(address, value);
	}

	std::uint16_t realAddress = address;
	if (realAddress >= Addr_ERAM_Start && realAddress <= Addr_ERAM_End)
		realAddress -= 0x2000;

	// std::cout << "writing \"" << std::hex << value << std::dec << "\" at addr: \"" << std::hex << address << std::dec << "\"" << std::endl;
	_ram[address] = value;
}
std::uint8_t MemoryBus::Read(const std::uint16_t& address)
{
	if (!IsAddressMapped(address))
		return 0xFF;

	if (address <= 0x7FFF)
	{
		if (_mapper != nullptr)
			return _mapper->Read(address);

		return _rom->Read(address);
	}

	std::uint16_t realAddress = address;
	if (realAddress >= Addr_ERAM_Start && realAddress <= Addr_ERAM_End)
		realAddress -= 0x2000;

	return _ram[realAddress];
}

uint8_t* MemoryBus::Get(const uint16_t& address)
{
	return _ram + translateAddress(address);
}

uint16_t MemoryBus::ReadWord(const uint16_t& address)
{
	if (!IsAddressMapped(address))
		return 0xFFFF;

	std::uint16_t realAddress = address;
	if (realAddress >= Addr_ERAM_Start && realAddress <= Addr_ERAM_End)
		realAddress -= 0x2000;

	uint16_t returnValue = _ram[realAddress];
	returnValue |= ((uint16_t)_ram[realAddress + 1] << 8);

	return returnValue;
}

void MemoryBus::RequestInterrupt(Interrupt interrupt)
{
	/*
	std::cout << "Interrupt Requested: ";
	switch (interrupt)
	{
	case Interrupt::VBLANK:
		std::cout << "VBLANK" << std::endl;
		break;
	case Interrupt::LCD:
		std::cout << "LCD" << std::endl;
		break;
	case Interrupt::TIMER:
		std::cout << "TIMER" << std::endl;
		break;
	case Interrupt::SERIAL:
		std::cout << "SERIAL" << std::endl;
		break;
	case Interrupt::JOYPAD:
		std::cout << "JOYPAD" << std::endl;
		break;
	}
	*/

	_ram[HardwareRegister::IF] |= (uint8_t)interrupt;
}
Interrupt MemoryBus::GetInterrupts()
{
	return (Interrupt)_ram[HardwareRegister::IF];
}