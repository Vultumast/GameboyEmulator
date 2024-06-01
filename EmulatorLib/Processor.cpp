#include "Processor.hpp"
#include "Constants.hpp"
#include "MemoryBus.hpp"


Processor::Processor()
{
	// TODO: SETUP INSTRUCTION TABLE
	// Maybe make four tables in "blocks" like Pan Docs?
}

uint8_t Processor::read(uint16_t addr)
{
	// read from bus
	return 0;
}

void Processor::write(uint16_t addr, uint8_t value)
{
	// write to bus
}

void Processor::reset()
{
	pc = 0x0100;
	sp = 0xFFFE;

	// These are values for the DMG model game boy, they're different for GBC
	a = 0x01;
	b = 0x00;
	c = 0x13;
	d = 0x00;
	e = 0xD8;
	f = 0x30; // This is wrong if the header checksum is 0x00 but I don't care
	h = 0x01;
	l = 0x4D;

	// Reset internal emulation variables
	addr = 0x0000;
	fetched = 0x00;
}

void Processor::interrupt()
{
	// TODO
}

void Processor::nmi()
{
	// TODO
}

void Processor::clock()
{
	// Cycle timer finished?
	if (remaining_cycles == 0)
	{
		// TODO
	}
	
	cycle_count++;
	remaining_cycles--;
}

uint8_t Processor::GetFlag(FLAGS flag)
{
	return ((f & flag) > 0) ? 1 : 0;
}

void Processor::SetFlag(FLAGS flag, bool value)
{
	if (value)
		f |= flag;
	else
		f &= ~flag;
}


// TODO: ADDRESSING MODES, OPERATIONS