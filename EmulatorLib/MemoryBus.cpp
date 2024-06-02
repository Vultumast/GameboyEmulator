#include "MemoryBus.hpp";
#include <algorithm>

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
	if (IsAddressMapped(address))
		return;

	std::uint16_t realAddress = address;
	if (realAddress >= Addr_ERAM_Start && realAddress <= Addr_ERAM_End)
		realAddress -= 0x2000;

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