#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

#include "Video.hpp"
#include "MemoryBus.hpp"
#include "ROMInfo.hpp"
#include "MBC1.hpp"
#include "OpCodeInfo.hpp"

#include <iterator>
#include <vector>

#define DLL_EXPORT __declspec(dllexport)

extern "C"
{
	DLL_EXPORT void pointer_delete(void* pointer) { delete pointer; }
	DLL_EXPORT uint8_t* create8kbank() { return new uint8_t[0x8000]; }




	DLL_EXPORT Video* video_create(MemoryBus* bus, HWND hwnd) { return new Video(bus, hwnd); }
	DLL_EXPORT void video_clear(Video* video) { video->Clear(); }
	DLL_EXPORT void video_present(Video* video) { video->Present(); }
	DLL_EXPORT void video_update(Video* video, uint32_t cycles) { video->Update(cycles); }
	DLL_EXPORT uint32_t video_getpixel(Video* video, uint8_t x, uint8_t y) { return video->GetPixel(x, y); }

	DLL_EXPORT MemoryBus* memorybus_create(ROMInfo* rominfo) { return new MemoryBus(rominfo); }
	DLL_EXPORT void memorybus_randomize(MemoryBus* pointer) { pointer->Randomize(); }
	DLL_EXPORT void memorybus_write(MemoryBus* pointer, uint16_t address, uint8_t value) { pointer->Write(address, value); }
	DLL_EXPORT uint8_t memorybus_read(MemoryBus* pointer, uint16_t address) { return pointer->Read(address); }
	DLL_EXPORT bool memorybus_isaddressmapped(MemoryBus* pointer, uint16_t* address) { return pointer->IsAddressMapped(*address); }

	DLL_EXPORT ROMInfo* rominfo_create(uint8_t* rominfo, uint32_t size) { return new ROMInfo(rominfo, size); }
	DLL_EXPORT uint8_t rominfo_getcartridgetype(ROMInfo* pointer) { return (uint8_t)pointer->GetCartridgeType(); }
	DLL_EXPORT uint8_t rominfo_getmappertype(ROMInfo* pointer) { return (uint8_t)pointer->GetMapperType(); }
	DLL_EXPORT uint32_t rominfo_getramsize(ROMInfo* pointer) { return pointer->GetRAMSize(); }
	DLL_EXPORT uint8_t rominfo_read(ROMInfo* pointer, uint32_t address) { return pointer->Read(address); }


	DLL_EXPORT uint8_t opcode_getopcode(uint8_t value) { return (uint8_t)OpCodeInfo::OpCodes[value].GetOpCode(); }
	DLL_EXPORT uint8_t opcode_getprefixopcode(uint8_t value) { return (uint8_t)OpCodeInfo::OpCodesCB[value].GetOpCode(); }

	DLL_EXPORT uint8_t opcode_getlhsoperand(uint8_t value) { return (uint8_t)OpCodeInfo::OpCodes[value].GetLeftHandOperand(); }
	DLL_EXPORT uint8_t opcode_getrhsoperand(uint8_t value) { return (uint8_t)OpCodeInfo::OpCodes[value].GetRightHandOperand(); }
	DLL_EXPORT uint8_t opcode_getprefixlhsoperand(uint8_t value) { return (uint8_t)OpCodeInfo::OpCodesCB[value].GetLeftHandOperand(); }
	DLL_EXPORT uint8_t opcode_getprefixrhsoperand(uint8_t value) { return (uint8_t)OpCodeInfo::OpCodesCB[value].GetRightHandOperand(); }

}