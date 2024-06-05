#pragma once

#include "Constants.hpp"
#include "MemoryBus.hpp"

#include <string>

enum class CartridgeType
{
	ROM_Only = 0x00,
	MBC1,
	MBC1_RAM,
	MBC1_RAM_BATTERY,

	MBC2 = 0x05,
	MBC2_RAM,

	ROM_RAM = 0x08,
	ROM_RAM_BATTERY,

	MMM01 = 0x0B,
	MMM01_RAM,
	MMM01_RAM_BATTERY,

	MBC3_TIMER_BATTERY = 0x0F,
	MBC3_TIMER_RAM_BATTERY,
	MBC3,
	MBC3_RAM,
	MBC3_RAM_BATTERY,

	MBC5 = 0x19,
	MBC5_RAM = 0x1A,
	MBC5_RAM_BATTERY,
	MBC5_RUMBLE,
	MBC5_RUMBLE_RAM,
	MBC5_RUMBLE_RAM_BATTERY,

	MBC6 = 0x20,

	MBC7_SENSOR_RUMBLE_RAM_BATTERY = 0x22,

	POCKET_CAMERA = 0xFC,
	BANDAI_TAMA5 = 0xFD,
	HuC3 = 0xFE,
	HuC1_RAM_BATTERY = 0xFF
};

enum class MapperType
{
	None,
	MBC1,
	MBC2,
	MBC3,
	MBC5,
	MBC6,
	MBC7,
	MMM01,
	HuC1,
	HuC3,
	TAMA5
};

class RomInfo
{
private:
	std::string _gameName = "";
	uint8_t _cartType = 0x00;
	uint8_t _ramSize = 0x00;
	uint32_t _romSize = 0x00;
	uint8_t _revision = 0x00;
public:
	RomInfo(MemoryBus* memoryBus);

	const std::string& GetGameName() const;
	uint8_t GetRevision() const;

	uint8_t GetRawCartridgeType() const;

	CartridgeType GetCartridgeType() const;
	MapperType GetMapperType() const;

	bool HasRAM() const;
	bool HasBattery() const;
	bool HasRumble() const;

	uint32_t GetROMSize() const;
	uint32_t GetRAMSize() const;
};