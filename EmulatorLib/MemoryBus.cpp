#include "MemoryBus.hpp";
#include <algorithm>
#include <iostream>

void MemoryBus::Randomize()
{
	for (auto i = 0; i < 0x10000; i++)
		_ram[i] = rand() % 0xFF;
}

bool MemoryBus::IsAddressMapped(const std::uint16_t& address)
{

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

	std::uint16_t realAddress = address;
	if (realAddress >= Addr_ERAM_Start && realAddress <= Addr_ERAM_End)
		realAddress -= 0x2000;

	return _ram[realAddress];
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

void MemoryBus::WriteROM(const std::vector<uint8_t>& data)
{
	uint16_t expectedLength = (Addr_ROM_End - Addr_ROM_Start) + 1;

	if (expectedLength == data.size())
		std::copy(data.begin(), data.end(), _ram);
	else
		std::cout << "Rom data was outside of expected range." << std::endl;
}

void MemoryBus::RequestInterrupt(Interrupt interrupt)
{
	_ram[0xFF0F] |= (uint8_t)interrupt;
}
Interrupt MemoryBus::GetInterrupts()
{
	return (Interrupt)_ram[0xFF0F];
}