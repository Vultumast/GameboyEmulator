#include "Framework.hpp"

void pointer_delete(void* pointer) { delete pointer; }

uint8_t* create8kbank() { return new uint8_t[0x8000]; }

kitsemu::CPU* cpu_create(MemoryBus* bus) { return new kitsemu::CPU(*bus); }

uint16_t cpu_getregister(kitsemu::CPU* cpu, uint8_t reg)
{
	switch (reg)
	{
	case 0: // AF
		return cpu->AF();
	case 1: // BC
		return cpu->BC();
	case 2: // DE
		return cpu->DE();
	case 3: // HL
		return cpu->HL();
	case 4: // SP
		return cpu->SP();
	case 5: // PC
		return cpu->PC();
	case 6: // A
		return cpu->A();
	case 7: // B
		return cpu->B();
	case 8: // C
		return cpu->C();
	case 9: // D
		return cpu->D();
	case 10: // E
		return cpu->E();
	case 11: // H
		return cpu->H();
	case 12: // L
		return cpu->L();
	default:
		return 0;
	}
}

void cpu_setregister(kitsemu::CPU* cpu, uint8_t reg, uint16_t value)
{
	switch (reg)
	{
	case 0: // AF
		cpu->AF() = value;
		break;
	case 1: // BC
		cpu->BC() = value;
		break;
	case 2: // DE
		cpu->DE() = value;
		break;
	case 3: // HL
		cpu->HL() = value;
		break;
	case 4: // SP
		cpu->SP() = value;
		break;
	case 5: // PC
		cpu->PC() = value;
		break;
	case 6: // A
		cpu->A() = (value & 0xFF);
		break;
	case 7: // B
		cpu->B() = (value & 0xFF);
		break;
	case 8: // C
		cpu->C() = (value & 0xFF);
		break;
	case 9: // D
		cpu->D() = (value & 0xFF);
		break;
	case 10: // E
		cpu->E() = (value & 0xFF);
		break;
	case 11: // H
		cpu->H() = (value & 0xFF);
		break;
	case 12: // L
		cpu->L() = (value & 0xFF);
		break;
	}
}

uint8_t cpu_getcycles(kitsemu::CPU* cpu) { return cpu->GetCycles(); }
void cpu_execute(kitsemu::CPU* cpu) { return cpu->Execute(); }

Video* video_create(MemoryBus* bus, HWND hwnd) { return new Video(bus, hwnd); }
void video_clear(Video* video) { video->Clear(); }
void video_present(Video* video) { video->Present(); }
void video_update(Video* video, uint32_t cycles) { video->Update(cycles); }
uint32_t video_getpixel(Video* video, uint8_t x, uint8_t y) { return video->GetPixel(x, y); }

MemoryBus* memorybus_create(ROMInfo* rominfo) { return new MemoryBus(rominfo); }
void memorybus_randomize(MemoryBus* pointer) { pointer->Randomize(); }
void memorybus_write(MemoryBus* pointer, uint16_t address, uint8_t value) { pointer->Write(address, value); }
uint8_t memorybus_read(MemoryBus* pointer, uint16_t address) { return pointer->Read(address); }
bool memorybus_isaddressmapped(MemoryBus* pointer, uint16_t* address) { return pointer->IsAddressMapped(*address); }

ROMInfo* rominfo_create(uint8_t* rominfo, uint32_t size) { return new ROMInfo(rominfo, size); }
uint8_t rominfo_getcartridgetype(ROMInfo* pointer) { return (uint8_t)pointer->GetCartridgeType(); }
uint8_t rominfo_getmappertype(ROMInfo* pointer) { return (uint8_t)pointer->GetMapperType(); }
uint32_t rominfo_getramsize(ROMInfo* pointer) { return pointer->GetRAMSize(); }
uint8_t rominfo_read(ROMInfo* pointer, uint32_t address) { return pointer->Read(address); }


uint8_t opcode_getopcode(uint8_t value) { return (uint8_t)OpCodeInfo::OpCodes[value].GetOpCode(); }
uint8_t opcode_getprefixopcode(uint8_t value) { return (uint8_t)OpCodeInfo::OpCodesCB[value].GetOpCode(); }

uint8_t opcode_getlhsoperand(uint8_t value) { return (uint8_t)OpCodeInfo::OpCodes[value].GetLeftHandOperand(); }
uint8_t opcode_getrhsoperand(uint8_t value) { return (uint8_t)OpCodeInfo::OpCodes[value].GetRightHandOperand(); }
uint8_t opcode_getprefixlhsoperand(uint8_t value) { return (uint8_t)OpCodeInfo::OpCodesCB[value].GetLeftHandOperand(); }
uint8_t opcode_getprefixrhsoperand(uint8_t value) { return (uint8_t)OpCodeInfo::OpCodesCB[value].GetRightHandOperand(); }
