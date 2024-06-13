#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

#include "Processor.hpp"
#include "Video.hpp"
#include "MemoryBus.hpp"
#include "ROMInfo.hpp"
#include "MBC1.hpp"

#include <iterator>
#include <vector>

#define DLL_EXPORT __declspec(dllexport)

extern "C"
{
	DLL_EXPORT void pointer_delete(void* pointer) { delete pointer; }
	DLL_EXPORT uint8_t* create8kbank() { return new uint8_t[0x8000]; }

	DLL_EXPORT Processor* processor_create(MemoryBus* bus) { return new Processor(bus); }
	DLL_EXPORT void processor_reset(Processor* processor) { processor->Reset(); }
	DLL_EXPORT void processor_setregister(Processor* processor, uint8_t reg, uint16_t value) { processor->SetRegister(static_cast<Register>(reg), value); }
	DLL_EXPORT uint16_t processor_getregister(Processor* processor, uint8_t reg) { return processor->GetRegister(static_cast<Register>(reg)); }
	DLL_EXPORT void processor_pulseclock(Processor* processor) { return processor->PulseClock(); }
	DLL_EXPORT uint8_t processor_getremainingcycles(Processor* processor) { return processor->GetRemainingCycles(); }
	DLL_EXPORT uint8_t processor_getinterruptsenabled(Processor* processor) { return processor->InterruptMasterEnable; }
	DLL_EXPORT void processor_setinterruptsenabled(Processor* processor, uint8_t value) { processor->InterruptMasterEnable = value; }


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
	DLL_EXPORT void memorybus_writerom(MemoryBus* pointer, uint8_t** data, uint16_t* size) { pointer->WriteROM(std::vector<uint8_t>(*data, *data + *size)); }

	DLL_EXPORT ROMInfo* rominfo_create(uint8_t* rominfo, uint32_t size) { return new ROMInfo(rominfo, size); }
	DLL_EXPORT uint8_t rominfo_getcartridgetype(ROMInfo* pointer) { return (uint8_t)pointer->GetCartridgeType(); }
	DLL_EXPORT uint8_t rominfo_getmappertype(ROMInfo* pointer) { return (uint8_t)pointer->GetMapperType(); }
	DLL_EXPORT uint32_t rominfo_getramsize(ROMInfo* pointer) { return pointer->GetRAMSize(); }
	DLL_EXPORT uint8_t rominfo_read(ROMInfo* pointer, uint32_t address) { return pointer->Read(address); }

}