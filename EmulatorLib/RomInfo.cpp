#include "RomInfo.hpp"

#include <iostream>

ROMInfo::ROMInfo(uint8_t* rom, uint32_t size)
{
	_rom = new uint8_t[size];
	std::memcpy(_rom, rom, size);

	std::cout << "creating rom with size: " << size << std::endl;
	for (uint16_t i = 0x0134; i < 0x143; i++)
	{
		char c = (char)_rom[i];

		if (c == 0x00)
			break;

		_gameName += c;
	}

	_cartType = _rom[0x147];

	_romSize = 32000 << _rom[0x148];
	switch (_rom[0x148])
	{
	case 0x01:
		_ramSize = 2000;
		break;
	case 0x02:
		_ramSize = 8000;
		break;
	case 0x03:
		_ramSize = 32000;
		break;
	case 0x04:
		_ramSize = 128000;
		break;
	case 0x05:
		_ramSize = 64000;
		break;
	default:
		_ramSize = 0x00;
		break;
	}
	_ramSize = 32000 << _rom[0x148];

	_revision = _rom[0x14C];
}
ROMInfo::~ROMInfo()
{
	if (_rom != nullptr)
		delete _rom;

	_rom = nullptr;
	size = 0;
}

const std::string& ROMInfo::GetGameName() const
{
	return _gameName;
}
uint8_t ROMInfo::GetRevision() const
{
	return _revision;
}

uint8_t ROMInfo::GetRawCartridgeType() const
{
	return _cartType;
}

CartridgeType ROMInfo::GetCartridgeType() const
{
	return (CartridgeType)_cartType;
}
MapperType ROMInfo::GetMapperType() const
{
	switch ((CartridgeType)_cartType)
	{
	case CartridgeType::ROM_Only:
	case CartridgeType::ROM_RAM:
	case CartridgeType::ROM_RAM_BATTERY:
	case CartridgeType::POCKET_CAMERA:
		return MapperType::None;

	case CartridgeType::MBC1:
	case CartridgeType::MBC1_RAM:
	case CartridgeType::MBC1_RAM_BATTERY:
		return MapperType::MBC1;

	case CartridgeType::MBC2:
	case CartridgeType::MBC2_RAM:
		return MapperType::MBC2;

	case CartridgeType::MMM01:
	case CartridgeType::MMM01_RAM:
	case CartridgeType::MMM01_RAM_BATTERY:
		return MapperType::MMM01;

	case CartridgeType::MBC3_TIMER_BATTERY:
	case CartridgeType::MBC3_TIMER_RAM_BATTERY:
	case CartridgeType::MBC3:
	case CartridgeType::MBC3_RAM:
	case CartridgeType::MBC3_RAM_BATTERY:
		return MapperType::MBC3;

	case CartridgeType::MBC5:
	case CartridgeType::MBC5_RAM:
	case CartridgeType::MBC5_RAM_BATTERY:
	case CartridgeType::MBC5_RUMBLE:
	case CartridgeType::MBC5_RUMBLE_RAM:
	case CartridgeType::MBC5_RUMBLE_RAM_BATTERY:
		return MapperType::MBC5;

	case CartridgeType::MBC6:
		return MapperType::MBC6;

	case CartridgeType::MBC7_SENSOR_RUMBLE_RAM_BATTERY:
		return MapperType::MBC7;

	case CartridgeType::BANDAI_TAMA5:
		return MapperType::TAMA5;

	case CartridgeType::HuC1_RAM_BATTERY:
		return MapperType::HuC1;

	case CartridgeType::HuC3:
		return MapperType::HuC3;
	}
}

bool ROMInfo::HasRAM() const
{
	switch ((CartridgeType)_cartType)
	{
	case CartridgeType::ROM_Only:
	case CartridgeType::MBC1:
	case CartridgeType::MBC2:
	case CartridgeType::MMM01:
	case CartridgeType::MBC3_TIMER_BATTERY:
	case CartridgeType::MBC3:
	case CartridgeType::MBC5:	
	case CartridgeType::MBC5_RUMBLE:
	case CartridgeType::MBC5_RUMBLE_RAM:
	case CartridgeType::MBC6:
	case CartridgeType::POCKET_CAMERA:
	case CartridgeType::BANDAI_TAMA5:
	case CartridgeType::HuC3:
		return false;

	case CartridgeType::MBC1_RAM:
	case CartridgeType::MBC1_RAM_BATTERY:
	case CartridgeType::MBC2_RAM:
	case CartridgeType::ROM_RAM:
	case CartridgeType::ROM_RAM_BATTERY:
	case CartridgeType::MMM01_RAM:
	case CartridgeType::MMM01_RAM_BATTERY:
	case CartridgeType::MBC3_TIMER_RAM_BATTERY:
	case CartridgeType::MBC3_RAM:
	case CartridgeType::MBC3_RAM_BATTERY:
	case CartridgeType::MBC5_RAM:
	case CartridgeType::MBC5_RAM_BATTERY:
	case CartridgeType::MBC5_RUMBLE_RAM_BATTERY:
	case CartridgeType::MBC7_SENSOR_RUMBLE_RAM_BATTERY:
	case CartridgeType::HuC1_RAM_BATTERY:
		return true;
	}
}
bool ROMInfo::HasBattery() const
{
	switch ((CartridgeType)_cartType)
	{
	case CartridgeType::ROM_Only:
	case CartridgeType::MBC1:
	case CartridgeType::MBC1_RAM:
	case CartridgeType::MBC2:
	case CartridgeType::MBC2_RAM:
	case CartridgeType::ROM_RAM:
	case CartridgeType::MMM01:
	case CartridgeType::MMM01_RAM:
	case CartridgeType::MBC3:
	case CartridgeType::MBC3_RAM:
	case CartridgeType::MBC5:
	case CartridgeType::MBC5_RAM:
	case CartridgeType::MBC5_RAM_BATTERY:
	case CartridgeType::MBC5_RUMBLE:
	case CartridgeType::MBC5_RUMBLE_RAM:
	case CartridgeType::MBC6:
	case CartridgeType::POCKET_CAMERA:
	case CartridgeType::BANDAI_TAMA5:
	case CartridgeType::HuC3:
		return false;
	case CartridgeType::MBC1_RAM_BATTERY:
	case CartridgeType::ROM_RAM_BATTERY:
	case CartridgeType::MMM01_RAM_BATTERY:
	case CartridgeType::MBC3_TIMER_BATTERY:
	case CartridgeType::MBC3_TIMER_RAM_BATTERY:
	case CartridgeType::MBC3_RAM_BATTERY:
	case CartridgeType::MBC5_RUMBLE_RAM_BATTERY:
	case CartridgeType::MBC7_SENSOR_RUMBLE_RAM_BATTERY:
	case CartridgeType::HuC1_RAM_BATTERY:
		return true;
	}
}
bool ROMInfo::HasRumble() const
{
	switch ((CartridgeType)_cartType)
	{
	case CartridgeType::ROM_Only:
	case CartridgeType::MBC1:
	case CartridgeType::MBC1_RAM:
	case CartridgeType::MBC1_RAM_BATTERY:
	case CartridgeType::MBC2:
	case CartridgeType::MBC2_RAM:
	case CartridgeType::ROM_RAM:
	case CartridgeType::ROM_RAM_BATTERY:
	case CartridgeType::MMM01:
	case CartridgeType::MMM01_RAM:
	case CartridgeType::MMM01_RAM_BATTERY:
	case CartridgeType::MBC3_TIMER_BATTERY:
	case CartridgeType::MBC3_TIMER_RAM_BATTERY:
	case CartridgeType::MBC3:
	case CartridgeType::MBC3_RAM:
	case CartridgeType::MBC3_RAM_BATTERY:
	case CartridgeType::MBC5:
	case CartridgeType::MBC5_RAM:
	case CartridgeType::MBC5_RAM_BATTERY:
	case CartridgeType::MBC6:
	case CartridgeType::POCKET_CAMERA:
	case CartridgeType::BANDAI_TAMA5:
	case CartridgeType::HuC3:
	case CartridgeType::HuC1_RAM_BATTERY:
		return false;
	case CartridgeType::MBC5_RUMBLE:
	case CartridgeType::MBC5_RUMBLE_RAM:
	case CartridgeType::MBC5_RUMBLE_RAM_BATTERY:
	case CartridgeType::MBC7_SENSOR_RUMBLE_RAM_BATTERY:
		return true;
	}
}

uint32_t ROMInfo::GetROMSize() const
{
	return _romSize;
}
uint32_t ROMInfo::GetRAMSize() const
{
	return _ramSize;
}

uint8_t ROMInfo::Read(uint32_t address) const
{
	if (_rom == nullptr || address >= _romSize)
		return 0xFF;

	return _rom[address];
}