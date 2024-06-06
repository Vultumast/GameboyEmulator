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

	if (address >= 0xFF00) // Check IO Registers
	{
		if (address > Reg_Audio_End && address < Reg_WavePattern_Start)
			return false;
		if (address > Reg_LCDControl_End && address < Reg_VRAMBankSelect)
			return false;
		if (address > Reg_VRAMDMA_End && address < Reg_BGOBJPalettes_Start)
			return false;
		if (address > Reg_BGOBJPalettes_End && address < Reg_WRAMBankSelect)
			return false;
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

void MemoryBus::WriteROM(const std::vector<uint8_t>& data)
{
	uint16_t expectedLength = (Addr_ROM_End - Addr_ROM_Start) + 1;

	if (expectedLength == data.size())
		std::copy(data.begin(), data.end(), _ram);
	else
		std::cout << "Rom data was outside of expected range." << std::endl;
}

void MemoryBus::SetInterrupt(Interrupt interrupt, bool value)
{
	uint8_t currentInterrupt = (_ram[0xFF0F] & (uint8_t)interrupt);

	if (value)
		currentInterrupt |= (uint8_t)interrupt;

	_ram[0xFF0F] = currentInterrupt;
}
Interrupt MemoryBus::GetInterrupts()
{
	return (Interrupt)_ram[0xFF0F];
}