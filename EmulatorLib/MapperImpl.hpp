#pragma once

#include <cstdint>

class ROMInfo;

class MapperImpl
{
private:
	ROMInfo* _romReference = nullptr;

protected:
	uint8_t _romBank = 1;
	uint8_t _ramBank = 0;

	bool _ramEnabled = false;
	bool _rumbleEnabled = false;



public:
	MapperImpl(ROMInfo* rom)
	{
		_romReference = rom;
	}

	virtual void Write(uint16_t address, uint8_t value) = 0;
	virtual uint8_t Read(uint16_t address) = 0;

	virtual void Reset() = 0;

	ROMInfo* GetROMInfo() { return _romReference; }

	uint8_t GetROMBank() { return _romBank; }

	bool IsRAMEnabled() { return _ramEnabled; }
	bool IsRumbleEnabled() { return _rumbleEnabled; }
};