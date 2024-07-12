#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

#include "CPU.hpp"
#include "Video.hpp"
#include "MemoryBus.hpp"
#include "ROMInfo.hpp"
#include "MBC1.hpp"
#include "OpCodeInfo.hpp"

#include <iterator>
#include <vector>

#include "Export.hpp"

extern "C"
{
	EMULATOR_API void pointer_delete(void* pointer);
	EMULATOR_API uint8_t* create8kbank();

	EMULATOR_API kitsemu::CPU* cpu_create(MemoryBus* bus);
	EMULATOR_API uint16_t cpu_getregister(kitsemu::CPU* cpu, uint8_t reg);
	EMULATOR_API void cpu_setregister(kitsemu::CPU* cpu, uint8_t reg, uint16_t value);

	EMULATOR_API uint8_t cpu_getcycles(kitsemu::CPU* cpu);
	EMULATOR_API void cpu_execute(kitsemu::CPU* cpu);

	EMULATOR_API Video* video_create(MemoryBus* bus, HWND hwnd);
	EMULATOR_API void video_clear(Video* video);
	EMULATOR_API void video_present(Video* video);
	EMULATOR_API void video_update(Video* video, uint32_t cycles);
	EMULATOR_API uint32_t video_getpixel(Video* video, uint8_t x, uint8_t y);

	EMULATOR_API MemoryBus* memorybus_create(ROMInfo* rominfo);
	EMULATOR_API void memorybus_randomize(MemoryBus* pointer);
	EMULATOR_API void memorybus_write(MemoryBus* pointer, uint16_t address, uint8_t value);
	EMULATOR_API uint8_t memorybus_read(MemoryBus* pointer, uint16_t address);
	EMULATOR_API bool memorybus_isaddressmapped(MemoryBus* pointer, uint16_t* address);

	EMULATOR_API ROMInfo* rominfo_create(uint8_t* rominfo, uint32_t size);
	EMULATOR_API uint8_t rominfo_getcartridgetype(ROMInfo* pointer);
	EMULATOR_API uint8_t rominfo_getmappertype(ROMInfo* pointer);
	EMULATOR_API uint32_t rominfo_getramsize(ROMInfo* pointer);
	EMULATOR_API uint8_t rominfo_read(ROMInfo* pointer, uint32_t address);


	EMULATOR_API uint8_t opcode_getopcode(uint8_t value);
	EMULATOR_API uint8_t opcode_getprefixopcode(uint8_t value);

	EMULATOR_API uint8_t opcode_getlhsoperand(uint8_t value);
	EMULATOR_API uint8_t opcode_getrhsoperand(uint8_t value);
	EMULATOR_API uint8_t opcode_getprefixlhsoperand(uint8_t value);
	EMULATOR_API uint8_t opcode_getprefixrhsoperand(uint8_t value);

}