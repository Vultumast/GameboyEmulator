#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

#include "Processor.hpp"

#define DLL_EXPORT __declspec(dllexport)

extern "C"
{
	DLL_EXPORT Processor* processor_create() { return new Processor(); }
	DLL_EXPORT void processor_delete(Processor* pointer) { delete pointer; }

	DLL_EXPORT void processor_reset(Processor* processor) { processor->reset(); }
}