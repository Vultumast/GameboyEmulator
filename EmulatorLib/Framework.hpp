#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

#include "Processor.hpp"
#include "Video.hpp"

#define DLL_EXPORT __declspec(dllexport)

extern "C"
{
	DLL_EXPORT Processor* processor_create(MemoryBus* bus) { return new Processor(bus); }
	DLL_EXPORT void processor_delete(Processor* pointer) { delete pointer; }

	DLL_EXPORT void processor_reset(Processor* processor) { processor->Reset(); }



	DLL_EXPORT Video* video_create(MemoryBus* bus, HWND hwnd) { return new Video(bus, hwnd); }
	DLL_EXPORT void video_delete(Video* pointer) { delete pointer; }

	DLL_EXPORT void video_clear(Video* video) { video->Clear(); }
	DLL_EXPORT void video_present(Video* video) { video->Present(); }
}