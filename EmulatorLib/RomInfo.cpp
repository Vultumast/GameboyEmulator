#include "RomInfo.hpp"

RomInfo::RomInfo(MemoryBus* memoryBus)
{
	if (memoryBus == nullptr)
		return;

	for (uint16_t i = 0x0134; i < 0x143; i++)
	{
		char c = (char)memoryBus->Read(i);

		if (c == 0x00)
			break;

		_gameName += c;
	}

	_cartType = memoryBus->Read(0x147);

	_romSize = 32000 << memoryBus->Read(0x148);
	switch (memoryBus->Read(0x148))
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
	_ramSize = 32000 << memoryBus->Read(0x148);

	_revision = memoryBus->Read(0x14C);
}

const std::string& RomInfo::GetGameName() const
{
	return _gameName;
}
uint8_t RomInfo::GetRevision() const
{
	return _revision;
}

uint8_t RomInfo::GetRawCartridgeType() const
{
	return _cartType;
}

CartridgeType RomInfo::GetCartridgeType() const
{
	return (CartridgeType)_cartType;
}
MapperType RomInfo::GetMapperType() const
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

bool RomInfo::HasRAM() const
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
bool RomInfo::HasBattery() const
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
bool RomInfo::HasRumble() const
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

uint32_t RomInfo::GetROMSize() const
{
	return _romSize;
}
uint32_t RomInfo::GetRAMSize() const
{
	return _ramSize;
}