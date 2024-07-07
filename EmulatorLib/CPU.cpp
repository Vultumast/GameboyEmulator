#include "CPU.hpp"
#include "MemoryBus.hpp"

#pragma region OpCodes

#pragma region 8-bit
uint8_t kitsemu::CPU::opINC(uint8_t reg) // Z0H-
{
	uint8_t result = static_cast<uint8_t>(reg + 1);

	SetFlag(Flag::Z, result == 0);
	SetFlag(Flag::N, false);
	SetFlag(Flag::H, ((reg & 0xF) + 1) > 0x0F);

	return result;
}
uint8_t kitsemu::CPU::opDEC(uint8_t reg) // Z1H-
{
	uint8_t result = static_cast<uint8_t>(reg - 1);

	SetFlag(Flag::Z, result == 0);
	SetFlag(Flag::N, false);
	SetFlag(Flag::H, (reg & 0xF) < 1);

	return result;
}
void kitsemu::CPU::opRLCA() // 000C
{
	ClearFlags();
	SetFlag(Flag::C, (A() & 0x80) != 0);

	A() = static_cast<uint8_t>((A() << 1) | (A() >> 7));
}
void kitsemu::CPU::opADDReg(uint16_t reg) // -0HC
{
	uint32_t result = _hl + reg;

	SetFlag(Flag::N, false);
	SetFlag(Flag::H, ((_hl & 0xFFF) + (reg & 0xFFF)) > 0xFFF);
	SetFlag(Flag::C, (result >> 16) != 0);

	_hl = result;
}
void kitsemu::CPU::opRRCA() // 000C
{
	ClearFlags();
	SetFlag(Flag::C, (A() & 0x01) != 0);

	A() = static_cast<uint8_t>((A() >> 1) | (A() << 7));
}
void kitsemu::CPU::opSTOP() // ----
{
	Stopped = true;
	_pc++;
}
void kitsemu::CPU::opRLA() // 000C
{
	bool previousCarry = GetFlag(Flag::C);

	ClearFlags();
	SetFlag(Flag::C, (A() & 0x80) != 0);

	A() = static_cast<uint8_t>((A() << 1) | (previousCarry ? 0x01 : 0x00));
}
void kitsemu::CPU::opRRA() // 000C
{
	bool previousCarry = GetFlag(Flag::C);

	ClearFlags();
	SetFlag(Flag::C, (A() & 0x01) != 0);

	A() = static_cast<uint8_t>((A() >> 1) | (previousCarry ? 0x80 : 0x00));
}
void kitsemu::CPU::opJR(bool condition) // ----
{
	int8_t value = _mmu->Read(_pc++);
	if (condition)
		_pc += (value);
	_cycles = JUMP_RELATIVE_CYCLES[condition];
}
void kitsemu::CPU::opDAA() // Z-0C
{
	if (GetFlagN())
	{
		if (GetFlagC())
			A() -= 0x60;
		if (GetFlagH())
			A() -= 0x06;
	}
	else
	{
		if (GetFlagC() || A() >= 0x99)
		{
			A() += 0x60;
			SetFlag(Flag::C, true);
		}
		if (GetFlagH() || (A() & 0x0F) > 0x9)
			A() += 0x06;
	}
	SetFlag(Flag::Z, A() == 0x00);
	SetFlag(Flag::H, false);
}
void kitsemu::CPU::opCPL() // -11-
{
	A() = static_cast<uint8_t>(~A());
	SetFlag(Flag::N, true);
	SetFlag(Flag::H, true);
}
void kitsemu::CPU::opSCF() // -001
{
	SetFlag(Flag::N, false);
	SetFlag(Flag::H, false);
	SetFlag(Flag::C, true);
}
void kitsemu::CPU::opCCF() // -00C
{
	SetFlag(Flag::N, false);
	SetFlag(Flag::H, false);
	SetFlag(Flag::C, !GetFlagC());
}
void kitsemu::CPU::opHALT() // ----
{
	// TODO: THIS MIGHT BE INCORRECT !!
	if (!IME)
	{
		if (_mmu->IE() == 0 && ((_mmu->IF() & 0x1F) == 0))
			Halted = true;
		else
		{
			// The "Halt Bug"
			_pc--;
		}
	}
}
void kitsemu::CPU::opADD(uint8_t value) // Z0HC
{
	uint8_t result = A() + value;

	SetFlag(Flag::Z, result == 0);
	SetFlag(Flag::N, false);
	SetFlag(Flag::H, (A() & 0x0F) + (value & 0x0F) > 0x0F);
	SetFlag(Flag::C, (A() + value) > 0xFF);
	A() = result;
}
void kitsemu::CPU::opADC(uint8_t value) // Z0HC
{
	uint8_t result = A() + value + GetFlagC();

	SetFlag(Flag::Z, result == 0);
	SetFlag(Flag::N, false);
	SetFlag(Flag::H, ((A() & 0x0F) + (value & 0x0F) + GetFlagC()) > 0x0F);
	SetFlag(Flag::C, (A() + value + GetFlagC()) > 0xFF);
	A() = result;
}
void kitsemu::CPU::opSUB(uint8_t value) // Z1HC
{
	uint8_t result = A() - value;

	SetFlag(Flag::Z, result == 0);
	SetFlag(Flag::N, false);
	SetFlag(Flag::H, (A() & 0x0F) < (value & 0x0F));
	SetFlag(Flag::C, A() < value);
	A() = result;
}
void kitsemu::CPU::opSBC(uint8_t value) // Z1HC
{
	uint8_t result = A() - value - GetFlagC();
	SetFlag(Flag::Z, result == 0);
	SetFlag(Flag::N, false);
	SetFlag(Flag::H, (A() & 0x0F) < ((value & 0x0F) + GetFlagC()));
	SetFlag(Flag::C, A() < (value + GetFlagC()));
	A() = result;
}
void kitsemu::CPU::opAND(uint8_t value) // Z010
{
	A() &= value;
	ClearFlags();
	SetFlag(Flag::Z, A() == 0);
	SetFlag(Flag::H, true);
}
void kitsemu::CPU::opXOR(uint8_t value) // Z000
{
	A() ^= value;
	ClearFlags();
	SetFlag(Flag::Z, A() == 0);
}
void kitsemu::CPU::opOR(uint8_t value) // Z000
{
	A() |= value;
	ClearFlags();
	SetFlag(Flag::Z, A() == 0);
}
void kitsemu::CPU::opCP(uint8_t value) // Z1HC
{
	uint8_t result = A() - value;

	SetFlag(Flag::Z, result == 0);
	SetFlag(Flag::N, false);
	SetFlag(Flag::H, (A() & 0x0F) < (value & 0x0F));
	SetFlag(Flag::C, A() < value);
}
void kitsemu::CPU::opRT(bool condition)
{
	if (condition)
		_pc = StackPop();
	
	_cycles += RETURN_CYCLES[condition];
}
void kitsemu::CPU::opJP(bool condition)
{
	if (condition)
		_pc = _mmu->ReadWord(_pc);
	else
		_pc += 2;

	_cycles += JUMP_CYCLES[condition];
}
void kitsemu::CPU::opCALL(bool condition)
{
	if (condition)
	{
		StackPush(_pc + 2);
		_pc = _mmu->ReadWord(_pc);
	}
	else
		_pc += 2;

	_cycles += CALL_CYCLES[condition];
}
void kitsemu::CPU::opPREFIX(uint8_t opcode)
{
	switch (opcode)
	{
	case 0x00: B() = opRLC(B());							break; // RLC B
	case 0x01: C() = opRLC(C());							break; // RLC C
	case 0x02: D() = opRLC(D());							break; // RLC D
	case 0x03: E() = opRLC(E());							break; // RLC E
	case 0x04: H() = opRLC(H());							break; // RLC H
	case 0x05: L() = opRLC(L());							break; // RLC L
	case 0x06: _mmu->Write(HL(), opRLC(_mmu->Read(HL())));	break; // RLC (HL)
	case 0x07: A() = opRLC(A());							break; // RLC A

	case 0x08: B() = opRRC(B());							break; // RRC B
	case 0x09: C() = opRRC(C());							break; // RRC C
	case 0x0A: D() = opRRC(D());							break; // RRC D
	case 0x0B: E() = opRRC(E());							break; // RRC E
	case 0x0C: H() = opRRC(H());							break; // RRC H
	case 0x0D: L() = opRRC(L());							break; // RRC L
	case 0x0E: _mmu->Write(HL(), opRRC(_mmu->Read(HL())));	break; // RRC (HL)
	case 0x0F: A() = opRRC(A());							break; // RRC A

	case 0x10: B() = opRL(B());								break; // RL B
	case 0x11: C() = opRL(C());								break; // RL C
	case 0x12: D() = opRL(D());								break; // RL D
	case 0x13: E() = opRL(E());								break; // RL E
	case 0x14: H() = opRL(H());								break; // RL H
	case 0x15: L() = opRL(L());								break; // RL L
	case 0x16: _mmu->Write(HL(), opRL(_mmu->Read(HL())));	break; // RL (HL)
	case 0x17: A() = opRL(A());								break; // RL A

	case 0x18: B() = opRR(B());								break; // RR B
	case 0x19: C() = opRR(C());								break; // RR C
	case 0x1A: D() = opRR(D());								break; // RR D
	case 0x1B: E() = opRR(E());								break; // RR E
	case 0x1C: H() = opRR(H());								break; // RR H
	case 0x1D: L() = opRR(L());								break; // RR L
	case 0x1E: _mmu->Write(HL(), opRR(_mmu->Read(HL())));	break; // RR (HL)
	case 0x1F: A() = opRR(A());								break; // RR A

	case 0x20: B() = opSLA(B());							break; // SLA B
	case 0x21: C() = opSLA(C());							break; // SLA C
	case 0x22: D() = opSLA(D());							break; // SLA D
	case 0x23: E() = opSLA(E());							break; // SLA E
	case 0x24: H() = opSLA(H());							break; // SLA H
	case 0x25: L() = opSLA(L());							break; // SLA L
	case 0x26: _mmu->Write(HL(), opSLA(_mmu->Read(HL())));	break; // SLA (HL)
	case 0x27: A() = opSLA(A());							break; // SLA A

	case 0x28: B() = opSRA(B());							break; // SRA B
	case 0x29: C() = opSRA(C());							break; // SRA C
	case 0x2A: D() = opSRA(D());							break; // SRA D
	case 0x2B: E() = opSRA(E());							break; // SRA E
	case 0x2C: H() = opSRA(H());							break; // SRA H
	case 0x2D: L() = opSRA(L());							break; // SRA L
	case 0x2E: _mmu->Write(HL(), opSRA(_mmu->Read(HL())));	break; // SRA (HL)
	case 0x2F: A() = opSRA(A());							break; // SRA A

	case 0x30: B() = opSWAP(B());							break; // SWAP B
	case 0x31: C() = opSWAP(C());							break; // SWAP C
	case 0x32: D() = opSWAP(D());							break; // SWAP D
	case 0x33: E() = opSWAP(E());							break; // SWAP E
	case 0x34: H() = opSWAP(H());							break; // SWAP H
	case 0x35: L() = opSWAP(L());							break; // SWAP L
	case 0x36: _mmu->Write(HL(), opSWAP(_mmu->Read(HL())));	break; // SWAP (HL)
	case 0x37: A() = opSWAP(A());							break; // SWAP A

	case 0x38: B() = opSRL(B());							break; // SRL B
	case 0x39: C() = opSRL(C());							break; // SRL C
	case 0x3A: D() = opSRL(D());							break; // SRL D
	case 0x3B: E() = opSRL(E());							break; // SRL E
	case 0x3C: H() = opSRL(H());							break; // SRL H
	case 0x3D: L() = opSRL(L());							break; // SRL L
	case 0x3E: _mmu->Write(HL(), opSRL(_mmu->Read(HL())));	break; // SRL (HL)
	case 0x3F: A() = opSRL(A());							break; // SRL A

	case 0x40: opBIT(0x01, B());				break; // BIT B
	case 0x41: opBIT(0x01, C());				break; // BIT C
	case 0x42: opBIT(0x01, D());				break; // BIT D
	case 0x43: opBIT(0x01, E());				break; // BIT E
	case 0x44: opBIT(0x01, H());				break; // BIT H
	case 0x45: opBIT(0x01, L());				break; // BIT L
	case 0x46: opBIT(0x01, _mmu->Read(HL()));	break; // BIT (HL)
	case 0x47: opBIT(0x01, A());				break; // BIT A

	case 0x48: opBIT(0x02, B());				break; // BIT B
	case 0x49: opBIT(0x02, C());				break; // BIT C
	case 0x4A: opBIT(0x02, D());				break; // BIT D
	case 0x4B: opBIT(0x02, E());				break; // BIT E
	case 0x4C: opBIT(0x02, H());				break; // BIT H
	case 0x4D: opBIT(0x02, L());				break; // BIT L
	case 0x4E: opBIT(0x02, _mmu->Read(HL()));	break; // BIT (HL)
	case 0x4F: opBIT(0x02, A());				break; // BIT A

	case 0x50: opBIT(0x04, B());				break; // BIT B
	case 0x51: opBIT(0x04, C());				break; // BIT C
	case 0x52: opBIT(0x04, D());				break; // BIT D
	case 0x53: opBIT(0x04, E());				break; // BIT E
	case 0x54: opBIT(0x04, H());				break; // BIT H
	case 0x55: opBIT(0x04, L());				break; // BIT L
	case 0x56: opBIT(0x04, _mmu->Read(HL()));	break; // BIT (HL)
	case 0x57: opBIT(0x04, A());				break; // BIT A

	case 0x58: opBIT(0x08, B());				break; // BIT B
	case 0x59: opBIT(0x08, C());				break; // BIT C
	case 0x5A: opBIT(0x08, D());				break; // BIT D
	case 0x5B: opBIT(0x08, E());				break; // BIT E
	case 0x5C: opBIT(0x08, H());				break; // BIT H
	case 0x5D: opBIT(0x08, L());				break; // BIT L
	case 0x5E: opBIT(0x08, _mmu->Read(HL()));	break; // BIT (HL)
	case 0x5F: opBIT(0x08, A());				break; // BIT A

	case 0x60: opBIT(0x10, B());				break; // BIT B
	case 0x61: opBIT(0x10, C());				break; // BIT C
	case 0x62: opBIT(0x10, D());				break; // BIT D
	case 0x63: opBIT(0x10, E());				break; // BIT E
	case 0x64: opBIT(0x10, H());				break; // BIT H
	case 0x65: opBIT(0x10, L());				break; // BIT L
	case 0x66: opBIT(0x10, _mmu->Read(HL()));	break; // BIT (HL)
	case 0x67: opBIT(0x10, A());				break; // BIT A

	case 0x68: opBIT(0x20, B());				break; // BIT B
	case 0x69: opBIT(0x20, C());				break; // BIT C
	case 0x6A: opBIT(0x20, D());				break; // BIT D
	case 0x6B: opBIT(0x20, E());				break; // BIT E
	case 0x6C: opBIT(0x20, H());				break; // BIT H
	case 0x6D: opBIT(0x20, L());				break; // BIT L
	case 0x6E: opBIT(0x20, _mmu->Read(HL()));	break; // BIT (HL)
	case 0x6F: opBIT(0x20, A());				break; // BIT A

	case 0x70: opBIT(0x40, B());				break; // BIT B
	case 0x71: opBIT(0x40, C());				break; // BIT C
	case 0x72: opBIT(0x40, D());				break; // BIT D
	case 0x73: opBIT(0x40, E());				break; // BIT E
	case 0x74: opBIT(0x40, H());				break; // BIT H
	case 0x75: opBIT(0x40, L());				break; // BIT L
	case 0x76: opBIT(0x40, _mmu->Read(HL()));	break; // BIT (HL)
	case 0x77: opBIT(0x40, A());				break; // BIT A

	case 0x78: opBIT(0x80, B());				break; // BIT B
	case 0x79: opBIT(0x80, C());				break; // BIT C
	case 0x7A: opBIT(0x80, D());				break; // BIT D
	case 0x7B: opBIT(0x80, E());				break; // BIT E
	case 0x7C: opBIT(0x80, H());				break; // BIT H
	case 0x7D: opBIT(0x80, L());				break; // BIT L
	case 0x7E: opBIT(0x80, _mmu->Read(HL()));	break; // BIT (HL)
	case 0x7F: opBIT(0x80, A());				break; // BIT A

	case 0x80: B() = opRES(0x01, B());								break; // RES B
	case 0x81: C() = opRES(0x01, C());								break; // RES C
	case 0x82: D() = opRES(0x01, D());								break; // RES D
	case 0x83: E() = opRES(0x01, E());								break; // RES E
	case 0x84: H() = opRES(0x01, H());								break; // RES H
	case 0x85: L() = opRES(0x01, L());								break; // RES L
	case 0x86: _mmu->Write(HL(), opRES(0x01, _mmu->Read(HL())));	break; // RES (HL)
	case 0x87: A() = opRES(0x01, A());								break; // RES A

	case 0x88: B() = opRES(0x02, B());								break; // RES B
	case 0x89: C() = opRES(0x02, C());								break; // RES C
	case 0x8A: D() = opRES(0x02, D());								break; // RES D
	case 0x8B: E() = opRES(0x02, E());								break; // RES E
	case 0x8C: H() = opRES(0x02, H());								break; // RES H
	case 0x8D: L() = opRES(0x02, L());								break; // RES L
	case 0x8E: _mmu->Write(HL(), opRES(0x02, _mmu->Read(HL())));	break; // RES (HL)
	case 0x8F: A() = opRES(0x02, A());								break; // RES A

	case 0x90: B() = opRES(0x04, B());								break; // RES B
	case 0x91: C() = opRES(0x04, C());								break; // RES C
	case 0x92: D() = opRES(0x04, D());								break; // RES D
	case 0x93: E() = opRES(0x04, E());								break; // RES E
	case 0x94: H() = opRES(0x04, H());								break; // RES H
	case 0x95: L() = opRES(0x04, L());								break; // RES L
	case 0x96: _mmu->Write(HL(), opRES(0x04, _mmu->Read(HL())));	break; // RES (HL)
	case 0x97: A() = opRES(0x04, A());								break; // RES A

	case 0x98: B() = opRES(0x08, B());								break; // RES B
	case 0x99: C() = opRES(0x08, C());								break; // RES C
	case 0x9A: D() = opRES(0x08, D());								break; // RES D
	case 0x9B: E() = opRES(0x08, E());								break; // RES E
	case 0x9C: H() = opRES(0x08, H());								break; // RES H
	case 0x9D: L() = opRES(0x08, L());								break; // RES L
	case 0x9E: _mmu->Write(HL(), opRES(0x08, _mmu->Read(HL())));	break; // RES (HL)
	case 0x9F: A() = opRES(0x08, A());								break; // RES A

	case 0xA0: B() = opRES(0x10, B());								break; // RES B
	case 0xA1: C() = opRES(0x10, C());								break; // RES C
	case 0xA2: D() = opRES(0x10, D());								break; // RES D
	case 0xA3: E() = opRES(0x10, E());								break; // RES E
	case 0xA4: H() = opRES(0x10, H());								break; // RES H
	case 0xA5: L() = opRES(0x10, L());								break; // RES L
	case 0xA6: _mmu->Write(HL(), opRES(0x10, _mmu->Read(HL())));	break; // RES (HL)
	case 0xA7: A() = opRES(0x10, A());								break; // RES A

	case 0xA8: B() = opRES(0x20, B());								break; // RES B
	case 0xA9: C() = opRES(0x20, C());								break; // RES C
	case 0xAA: D() = opRES(0x20, D());								break; // RES D
	case 0xAB: E() = opRES(0x20, E());								break; // RES E
	case 0xAC: H() = opRES(0x20, H());								break; // RES H
	case 0xAD: L() = opRES(0x20, L());								break; // RES L
	case 0xAE: _mmu->Write(HL(), opRES(0x20, _mmu->Read(HL())));	break; // RES (HL)
	case 0xAF: A() = opRES(0x20, A());								break; // RES A

	case 0xB0: B() = opRES(0x40, B());								break; // RES B
	case 0xB1: C() = opRES(0x40, C());								break; // RES C
	case 0xB2: D() = opRES(0x40, D());								break; // RES D
	case 0xB3: E() = opRES(0x40, E());								break; // RES E
	case 0xB4: H() = opRES(0x40, H());								break; // RES H
	case 0xB5: L() = opRES(0x40, L());								break; // RES L
	case 0xB6: _mmu->Write(HL(), opRES(0x40, _mmu->Read(HL())));	break; // RES (HL)
	case 0xB7: A() = opRES(0x40, A());								break; // RES A

	case 0xB8: B() = opRES(0x80, B());								break; // RES B
	case 0xB9: C() = opRES(0x80, C());								break; // RES C
	case 0xBA: D() = opRES(0x80, D());								break; // RES D
	case 0xBB: E() = opRES(0x80, E());								break; // RES E
	case 0xBC: H() = opRES(0x80, H());								break; // RES H
	case 0xBD: L() = opRES(0x80, L());								break; // RES L
	case 0xBE: _mmu->Write(HL(), opRES(0x80, _mmu->Read(HL())));	break; // RES (HL)
	case 0xBF: A() = opRES(0x80, A());								break; // RES A

	case 0xC0: B() = opSET(0x01, B());								break; // SET B
	case 0xC1: C() = opSET(0x01, C());								break; // SET C
	case 0xC2: D() = opSET(0x01, D());								break; // SET D
	case 0xC3: E() = opSET(0x01, E());								break; // SET E
	case 0xC4: H() = opSET(0x01, H());								break; // SET H
	case 0xC5: L() = opSET(0x01, L());								break; // SET L
	case 0xC6: _mmu->Write(HL(), opSET(0x01, _mmu->Read(HL())));	break; // SET (HL)
	case 0xC7: A() = opSET(0x01, A());								break; // SET A

	case 0xC8: B() = opSET(0x02, B());								break; // SET B
	case 0xC9: C() = opSET(0x02, C());								break; // SET C
	case 0xCA: D() = opSET(0x02, D());								break; // SET D
	case 0xCB: E() = opSET(0x02, E());								break; // SET E
	case 0xCC: H() = opSET(0x02, H());								break; // SET H
	case 0xCD: L() = opSET(0x02, L());								break; // SET L
	case 0xCE: _mmu->Write(HL(), opSET(0x02, _mmu->Read(HL())));	break; // SET (HL)
	case 0xCF: A() = opSET(0x02, A());								break; // SET A

	case 0xD0: B() = opSET(0x04, B());								break; // SET B
	case 0xD1: C() = opSET(0x04, C());								break; // SET C
	case 0xD2: D() = opSET(0x04, D());								break; // SET D
	case 0xD3: E() = opSET(0x04, E());								break; // SET E
	case 0xD4: H() = opSET(0x04, H());								break; // SET H
	case 0xD5: L() = opSET(0x04, L());								break; // SET L
	case 0xD6: _mmu->Write(HL(), opSET(0x04, _mmu->Read(HL())));	break; // SET (HL)
	case 0xD7: A() = opSET(0x04, A());								break; // SET A

	case 0xD8: B() = opSET(0x08, B());								break; // SET B
	case 0xD9: C() = opSET(0x08, C());								break; // SET C
	case 0xDA: D() = opSET(0x08, D());								break; // SET D
	case 0xDB: E() = opSET(0x08, E());								break; // SET E
	case 0xDC: H() = opSET(0x08, H());								break; // SET H
	case 0xDD: L() = opSET(0x08, L());								break; // SET L
	case 0xDE: _mmu->Write(HL(), opSET(0x08, _mmu->Read(HL())));	break; // SET (HL)
	case 0xDF: A() = opSET(0x08, A());								break; // SET A

	case 0xE0: B() = opSET(0x10, B());								break; // SET B
	case 0xE1: C() = opSET(0x10, C());								break; // SET C
	case 0xE2: D() = opSET(0x10, D());								break; // SET D
	case 0xE3: E() = opSET(0x10, E());								break; // SET E
	case 0xE4: H() = opSET(0x10, H());								break; // SET H
	case 0xE5: L() = opSET(0x10, L());								break; // SET L
	case 0xE6: _mmu->Write(HL(), opSET(0x10, _mmu->Read(HL())));	break; // SET (HL)
	case 0xE7: A() = opSET(0x10, A());								break; // SET A

	case 0xE8: B() = opSET(0x20, B());								break; // SET B
	case 0xE9: C() = opSET(0x20, C());								break; // SET C
	case 0xEA: D() = opSET(0x20, D());								break; // SET D
	case 0xEB: E() = opSET(0x20, E());								break; // SET E
	case 0xEC: H() = opSET(0x20, H());								break; // SET H
	case 0xED: L() = opSET(0x20, L());								break; // SET L
	case 0xEE: _mmu->Write(HL(), opSET(0x20, _mmu->Read(HL())));	break; // SET (HL)
	case 0xEF: A() = opSET(0x20, A());								break; // SET A

	case 0xF0: B() = opSET(0x40, B());								break; // SET B
	case 0xF1: C() = opSET(0x40, C());								break; // SET C
	case 0xF2: D() = opSET(0x40, D());								break; // SET D
	case 0xF3: E() = opSET(0x40, E());								break; // SET E
	case 0xF4: H() = opSET(0x40, H());								break; // SET H
	case 0xF5: L() = opSET(0x40, L());								break; // SET L
	case 0xF6: _mmu->Write(HL(), opSET(0x40, _mmu->Read(HL())));	break; // SET (HL)
	case 0xF7: A() = opSET(0x40, A());								break; // SET A

	case 0xF8: B() = opSET(0x80, B());								break; // SET B
	case 0xF9: C() = opSET(0x80, C());								break; // SET C
	case 0xFA: D() = opSET(0x80, D());								break; // SET D
	case 0xFB: E() = opSET(0x80, E());								break; // SET E
	case 0xFC: H() = opSET(0x80, H());								break; // SET H
	case 0xFD: L() = opSET(0x80, L());								break; // SET L
	case 0xFE: _mmu->Write(HL(), opSET(0x80, _mmu->Read(HL())));	break; // SET (HL)
	case 0xFF: A() = opSET(0x80, A());								break; // SET A
	}
}
uint16_t kitsemu::CPU::opADDImmediate(uint8_t value)
{
	int8_t immediate = _mmu->Read(_pc++);
	uint16_t result = value + immediate;

	SetFlag(Flag::Z, false);
	SetFlag(Flag::N, false);
	SetFlag(Flag::H, ((immediate & 0xF) + (value & 0xF)) > 0xF);
	SetFlag(Flag::C, (result >> 8) != 0);
	return result;
}
#pragma endregion

#pragma region 16-bit
uint8_t kitsemu::CPU::opRLC(uint8_t byte) // Z00C
{
	uint8_t result = static_cast<uint8_t>((byte << 1) | (byte >> 7));

	SetFlag(Flag::Z, result == 0);
	SetFlag(Flag::N, false);
	SetFlag(Flag::H, false);
	SetFlag(Flag::C, (byte & 0x80) != 0);
	return result;
}
uint8_t kitsemu::CPU::opRRC(uint8_t byte) // Z00C
{
	uint8_t result = static_cast<uint8_t>((byte >> 1) | (byte << 7));

	SetFlag(Flag::Z, result == 0);
	SetFlag(Flag::N, false);
	SetFlag(Flag::H, false);
	SetFlag(Flag::C, (byte & 0x1) != 0);
	return result;
}
uint8_t kitsemu::CPU::opRL(uint8_t byte) // Z00C
{
	uint8_t result = static_cast<uint8_t>((byte << 1) | (GetFlag(Flag::C) ? 0b1 : 0b0));
	SetFlag(Flag::Z, result == 0);
	SetFlag(Flag::N, false);
	SetFlag(Flag::H, false);
	SetFlag(Flag::C, (byte & 0x80) != 0);
	return result;
}
uint8_t kitsemu::CPU::opRR(uint8_t byte) // Z00C
{
	uint8_t result = static_cast<uint8_t>((byte >> 1) | (GetFlag(Flag::C) ? 0x80 : 0x00));
	SetFlag(Flag::Z, result == 0);
	SetFlag(Flag::N, false);
	SetFlag(Flag::H, false);
	SetFlag(Flag::C, (byte & 0x1) != 0);
	return result;
}
uint8_t kitsemu::CPU::opSLA(uint8_t byte) // Z00C
{
	uint8_t result = static_cast<uint8_t>(byte << 1);
	SetFlag(Flag::Z, result == 0);
	SetFlag(Flag::N, false);
	SetFlag(Flag::H, false);
	SetFlag(Flag::C, (byte & 0x80) != 0);
	return result;
}
uint8_t kitsemu::CPU::opSRA(uint8_t byte) // Z00C
{
	uint8_t result = static_cast<uint8_t>((byte << 1) |(byte & 0x80));
	SetFlag(Flag::Z, result == 0);
	SetFlag(Flag::N, false);
	SetFlag(Flag::H, false);
	SetFlag(Flag::C, (byte & 0x01) != 0);
	return result;
}
uint8_t kitsemu::CPU::opSWAP(uint8_t byte) // Z000
{
	uint8_t result = static_cast<uint8_t>(((byte & 0xF0) >> 4) | ((byte & 0x0F) << 4));
	SetFlag(Flag::Z, result == 0);
	SetFlag(Flag::N, false);
	SetFlag(Flag::H, false);
	SetFlag(Flag::C, false);
	return result;
}
uint8_t kitsemu::CPU::opSRL(uint8_t byte) // Z00C
{
	uint8_t result = static_cast<uint8_t>(byte >> 1);
	SetFlag(Flag::Z, result == 0);
	SetFlag(Flag::N, false);
	SetFlag(Flag::H, false);
	SetFlag(Flag::C, (byte & 0x01) != 0);
	return result;
}
uint8_t kitsemu::CPU::opSET(uint8_t byte, uint8_t reg) // ----
{
	return reg | byte;
}
uint8_t kitsemu::CPU::opRES(uint8_t byte, uint8_t reg) // ----
{
	return reg & ~byte;
}
void kitsemu::CPU::opBIT(uint8_t byte, uint8_t reg) // Z01-
{
	SetFlag(Flag::Z, (reg & byte) == 0);
	SetFlag(Flag::N, false);
	SetFlag(Flag::H, false);
}
#pragma endregion

#pragma endregion

void kitsemu::CPU::Reset()
{
	IME = false;
	Halted = false;
	Stopped = false;

	_pc = 0;
	_sp = 0;

	_af = 0;
	_bc = 0;
	_de = 0;
	_hl = 0;
}

void kitsemu::CPU::Execute()
{
	if (Stopped)
		return;

	// Prevent invalid flags
	_af &= 0xFFF0;

	uint8_t opcode = _mmu->Read(_pc++);
	_cycles = 0;

	switch (opcode)
	{
	case 0x00:										break; // NOP
	case 0x01: _bc = _mmu->ReadWord(_pc); _pc += 2; break; // LD BC,D16
	case 0x02: _mmu->Write(_bc, A());				break; // LD (BC),A
	case 0x03: _bc++;								break; // INC BC
	case 0x04: B() = opINC(B());					break; // INC B
	case 0x05: B() = opDEC(B());					break; // DEC B
	case 0x06: B() = _mmu->Read(_pc++);				break; // LD B,D8
	case 0x07: opRLCA();							break; // RLCA

	case 0x08: _mmu->WriteWord(_mmu->ReadWord(_pc), _sp); _pc += 2;		break; // LD (A16),SP
	case 0x09: opADDReg(_bc);											break; // ADD HL,BC
	case 0x0A: A() = _mmu->Read(_bc);									break; // LD A,(BC)
	case 0x0B: _bc--;													break; // DEC BC
	case 0x0C: C() = opINC(C());										break; // INC C
	case 0x0D: C() = opDEC(C());										break; // DEC C
	case 0x0E: C() = _mmu->Read(_pc++);									break; // LD C,D8
	case 0x0F: opRRCA();												break; // RRCA


	case 0x10:	opSTOP();							break; // STOP
	case 0x11: _de = _mmu->ReadWord(_pc); _pc += 2; break; // LD DE,D16
	case 0x12: _mmu->Write(_de, A());				break; // LD (DE),A
	case 0x13: _de++;								break; // INC DE
	case 0x14: D() = opINC(D());					break; // INC D
	case 0x15: D() = opDEC(D());					break; // DEC D
	case 0x16: D() = _mmu->Read(_pc++);				break; // LD D,D8
	case 0x17: opRLA();								break; // RLA

	case 0x18: opJR(true);					break; // JR D8
	case 0x19: opADDReg(_de);				break; // ADD HL,DE
	case 0x1A: A() = _mmu->Read(_de);		break; // LD A,(DE)
	case 0x1B: _de--;						break; // DEC DE
	case 0x1C: E() = opINC(E());			break; // INC E
	case 0x1D: E() = opDEC(E());			break; // DEC E
	case 0x1E: E() = _mmu->Read(_pc++);		break; // LD E,D8
	case 0x1F: opRRA();						break; // RRA


	case 0x20: opJR(!GetFlagZ());					break; // JR NZ,D8
	case 0x21: _hl = _mmu->ReadWord(_pc); _pc += 2;	break; // LD HL,D16
	case 0x22: _mmu->Write(_hl++, A());				break; // LD (HL+),A
	case 0x23: _hl++;								break; // INC HL
	case 0x24: H() = opINC(H());					break; // INC H
	case 0x25: H() = opDEC(H());					break; // DEC H
	case 0x26: H() = _mmu->Read(_pc++);				break; // LD H,D8
	case 0x27: opDAA();								break; // DAA

	case 0x28: opJR(GetFlagZ());		break; // JR Z,D8
	case 0x29: opADDReg(_hl);			break; // ADD HL,HL
	case 0x2A: A() = _mmu->Read(_hl++); break; // LD A,(HL+)
	case 0x2B: _hl--;					break; // DEC HL
	case 0x2C: L() = opINC(L());		break; // INC L
	case 0x2D: L() = opDEC(L());		break; // DEC L
	case 0x2E: L() = _mmu->Read(_pc++);	break; // LD L,D8
	case 0x2F: opCPL();					break; // CPL


	case 0x30: opJR(!GetFlagC());							break; // JR NC,D8
	case 0x31: _sp = _mmu->ReadWord(_pc); _pc += 2;			break; // LD SP,D16
	case 0x32: _mmu->Write(_hl--, A());						break; // LD (HL-),A
	case 0x33: _sp++;										break; // INC SP
	case 0x34: _mmu->Write(HL(), opINC(_mmu->Read(HL())));	break; // INC (HL)
	case 0x35: _mmu->Write(HL(), opDEC(_mmu->Read(HL())));	break; // DEC (HL)
	case 0x36: _mmu->Write(HL(), _mmu->Read(_pc++));		break; // LD (HL),D8
	case 0x37: opSCF();										break; // SCF

	case 0x38: opJR(GetFlagC());		break; // JR C,D8
	case 0x39: opADDReg(_sp);			break; // ADD HL,SP
	case 0x3A: A() = _mmu->Read(_hl--); break; // LD A,(HL-)
	case 0x3B: _sp--;					break; // DEC SP
	case 0x3C: A() = opINC(A());		break; // INC A
	case 0x3D: A() = opDEC(A());		break; // DEC A
	case 0x3E: A() = _mmu->Read(_pc++);	break; // LD A,D8
	case 0x3F: opCCF();					break; // CCF


	case 0x40: B() = B();				break; // LD B,B
	case 0x41: B() = C();				break; // LD B,C
	case 0x42: B() = D();				break; // LD B,D
	case 0x43: B() = E();				break; // LD B,E
	case 0x44: B() = H();				break; // LD B,H
	case 0x45: B() = L();				break; // LD B,L
	case 0x46: B() = _mmu->Read(_hl);	break; // LD B,(HL)
	case 0x47: B() = A();				break; // LD B,A

	case 0x48: C() = B();				break; // LD C,B
	case 0x49: C() = C();				break; // LD C,C
	case 0x4A: C() = D();				break; // LD C,D
	case 0x4B: C() = E();				break; // LD C,E
	case 0x4C: C() = H();				break; // LD C,H
	case 0x4D: C() = L();				break; // LD C,L
	case 0x4E: C() = _mmu->Read(_hl);	break; // LD C,(HL)
	case 0x4F: C() = A();				break; // LD C,A


	case 0x50: D() = B();				break; // LD D,B
	case 0x51: D() = C();				break; // LD D,C
	case 0x52: D() = D();				break; // LD D,D
	case 0x53: D() = E();				break; // LD D,E
	case 0x54: D() = H();				break; // LD D,H
	case 0x55: D() = L();				break; // LD D,L
	case 0x56: D() = _mmu->Read(_hl);	break; // LD D,(HL)
	case 0x57: D() = A();				break; // LD D,A

	case 0x58: E() = B();				break; // LD E,B
	case 0x59: E() = C();				break; // LD E,C
	case 0x5A: E() = D();				break; // LD E,D
	case 0x5B: E() = E();				break; // LD E,E
	case 0x5C: E() = H();				break; // LD E,H
	case 0x5D: E() = L();				break; // LD E,L
	case 0x5E: E() = _mmu->Read(_hl);	break; // LD E,(HL)
	case 0x5F: E() = A();				break; // LD E,A


	case 0x60: H() = B();				break; // LD H,B
	case 0x61: H() = C();				break; // LD H,C
	case 0x62: H() = D();				break; // LD H,D
	case 0x63: H() = E();				break; // LD H,E
	case 0x64: H() = H();				break; // LD H,H
	case 0x65: H() = L();				break; // LD H,L
	case 0x66: H() = _mmu->Read(_hl);	break; // LD H,(HL)
	case 0x67: H() = A();				break; // LD H,A

	case 0x68: L() = B();				break; // LD L,B
	case 0x69: L() = C();				break; // LD L,C
	case 0x6A: L() = D();				break; // LD L,D
	case 0x6B: L() = E();				break; // LD L,E
	case 0x6C: L() = H();				break; // LD L,H
	case 0x6D: L() = L();				break; // LD L,L
	case 0x6E: L() = _mmu->Read(_hl);	break; // LD L,(HL)
	case 0x6F: L() = A();				break; // LD L,A


	case 0x70: _mmu->Write(HL(), B());	break; // LD (HL),B
	case 0x71: _mmu->Write(HL(), C());	break; // LD (HL),C
	case 0x72: _mmu->Write(HL(), D());	break; // LD (HL),D
	case 0x73: _mmu->Write(HL(), E());	break; // LD (HL),E
	case 0x74: _mmu->Write(HL(), H());	break; // LD (HL),H
	case 0x75: _mmu->Write(HL(), L());	break; // LD (HL),L
	case 0x76: opHALT();				break; // HALT
	case 0x77: _mmu->Write(HL(), A());	break; // LD (HL),A

	case 0x78: A() = B();				break; // LD A,B
	case 0x79: A() = C();				break; // LD A,C
	case 0x7A: A() = D();				break; // LD A,D
	case 0x7B: A() = E();				break; // LD A,E
	case 0x7C: A() = H();				break; // LD A,H
	case 0x7D: A() = L();				break; // LD A,L
	case 0x7E: A() = _mmu->Read(_hl);	break; // LD A,(HL)
	case 0x7F: A() = A();				break; // LD A,A


	case 0x80: opADD(B());				break; // ADD B
	case 0x81: opADD(C());				break; // ADD C
	case 0x82: opADD(D());				break; // ADD D
	case 0x83: opADD(E());				break; // ADD E
	case 0x84: opADD(H());				break; // ADD H
	case 0x85: opADD(L());				break; // ADD L
	case 0x86: opADD(_mmu->Read(_hl));	break; // ADD (HL)
	case 0x87: opADD(A());				break; // ADD A

	case 0x88: opADC(B());				break; // ADC B
	case 0x89: opADC(C());				break; // ADC C
	case 0x8A: opADC(D());				break; // ADC D
	case 0x8B: opADC(E());				break; // ADC E
	case 0x8C: opADC(H());				break; // ADC H
	case 0x8D: opADC(L());				break; // ADC L
	case 0x8E: opADC(_mmu->Read(_hl));	break; // ADC (HL)
	case 0x8F: opADC(A());				break; // ADC A


	case 0x90: opSUB(B());				break; // SUB B
	case 0x91: opSUB(C());				break; // SUB C
	case 0x92: opSUB(D());				break; // SUB D
	case 0x93: opSUB(E());				break; // SUB E
	case 0x94: opSUB(H());				break; // SUB H
	case 0x95: opSUB(L());				break; // SUB L
	case 0x96: opSUB(_mmu->Read(_hl));	break; // SUB (HL)
	case 0x97: opSUB(A());				break; // SUB A

	case 0x98: opSBC(B());				break; // SBC B
	case 0x99: opSBC(C());				break; // SBC C
	case 0x9A: opSBC(D());				break; // SBC D
	case 0x9B: opSBC(E());				break; // SBC E
	case 0x9C: opSBC(H());				break; // SBC H
	case 0x9D: opSBC(L());				break; // SBC L
	case 0x9E: opSBC(_mmu->Read(_hl));	break; // SBC (HL)
	case 0x9F: opSBC(A());				break; // SBC A


	case 0xA0: opAND(B());				break; // AND B
	case 0xA1: opAND(C());				break; // AND C
	case 0xA2: opAND(D());				break; // AND D
	case 0xA3: opAND(E());				break; // AND E
	case 0xA4: opAND(H());				break; // AND H
	case 0xA5: opAND(L());				break; // AND L
	case 0xA6: opAND(_mmu->Read(_hl));	break; // AND (HL)
	case 0xA7: opAND(A());				break; // AND A

	case 0xA8: opXOR(B());				break; // XOR B
	case 0xA9: opXOR(C());				break; // XOR C
	case 0xAA: opXOR(D());				break; // XOR D
	case 0xAB: opXOR(E());				break; // XOR E
	case 0xAC: opXOR(H());				break; // XOR H
	case 0xAD: opXOR(L());				break; // XOR L
	case 0xAE: opXOR(_mmu->Read(_hl));	break; // XOR (HL)
	case 0xAF: opXOR(A());				break; // XOR A


	case 0xB0: opOR(B());				break; // OR B
	case 0xB1: opOR(C());				break; // OR C
	case 0xB2: opOR(D());				break; // OR D
	case 0xB3: opOR(E());				break; // OR E
	case 0xB4: opOR(H());				break; // OR H
	case 0xB5: opOR(L());				break; // OR L
	case 0xB6: opOR(_mmu->Read(_hl));	break; // OR (HL)
	case 0xB7: opOR(A());				break; // OR A

	case 0xB8: opCP(B());				break; // CP B
	case 0xB9: opCP(C());				break; // CP C
	case 0xBA: opCP(D());				break; // CP D
	case 0xBB: opCP(E());				break; // CP E
	case 0xBC: opCP(H());				break; // CP H
	case 0xBD: opCP(L());				break; // CP L
	case 0xBE: opCP(_mmu->Read(_hl));	break; // CP (HL)
	case 0xBF: opCP(A());				break; // CP A


	case 0xC0: opRT(!GetFlagZ());			break; // RET NZ
	case 0xC1: _bc = StackPop();    		break; // POP BC
	case 0xC2: opJP(!GetFlagZ());			break; // JP NZ,A16
	case 0xC3: opJP(true);					break; // JP A16
	case 0xC4: opCALL(!GetFlagZ());			break; // CALL NZ,A16
	case 0xC5: StackPush(_bc);				break; // PUSH BC
	case 0xC6: opADD(_mmu->Read(_pc++));	break; // ADD A,D8
	case 0xC7: ResetVector(0x00);			break; // RST 0

	case 0xC8: opRT(GetFlagZ());				break; // RET Z
	case 0xC9: opRT(true);    					break; // RET
	case 0xCA: opJP(GetFlagZ());				break; // JP Z,A16
	case 0xCB: opPREFIX(_mmu->Read(_pc++));		break; // PREFIX
	case 0xCC: opCALL(GetFlagZ());				break; // CALL Z,A16
	case 0xCD: opCALL(true);					break; // CALL A16
	case 0xCE: opADC(_mmu->Read(_pc++));		break; // ADC A,D8
	case 0xCF: ResetVector(0x08);				break; // RST 1


	case 0xD0: opRT(!GetFlagC());			break; // RET NC
	case 0xD1: _de = StackPop();    		break; // POP DE
	case 0xD2: opJP(!GetFlagC());			break; // JP NC,A16
	//case 0xD3:            					break; // ILLEGAL OPCODE
	case 0xD4: opCALL(!GetFlagC());			break; // CALL NC,A16
	case 0xD5: StackPush(_de);				break; // PUSH DE
	case 0xD6: opSUB(_mmu->Read(_pc++));	break; // SUB A,D8
	case 0xD7: ResetVector(0x10);			break; // RST 2

	case 0xD8: opRT(GetFlagC());				break; // RET C
	case 0xD9: opRT(true); IME = true;    		break; // RETI
	case 0xDA: opJP(GetFlagC());				break; // JP C,A16
	// case 0xDB:									break; // ILLEGAL OPCODE
	case 0xDC: opCALL(GetFlagC());				break; // CALL C,A16
	// case 0xDD:                					break; // ILLEGAL OPCODE
	case 0xDE: opSBC(_mmu->Read(_pc++));		break; // SBC A,D8
	case 0xDF: ResetVector(0x18);				break; // RST 4


	case 0xE0: _mmu->Write(0xFF00 + _mmu->Read(_pc++), A());	break;
	case 0xE1: _hl = StackPop();								break;
	case 0xE2: _mmu->Write(0xFF00 + C(), A());					break;
	// case 0xE3:													break; ILLEGAL OPCODE
	// case 0xE4:													break; ILLEGAL OPCODE
	case 0xE5: StackPush(_hl);									break;
	case 0xE6: opAND(_mmu->Read(_pc++));						break;
	case 0xE7: ResetVector(0x20);								break;

	case 0xE8: _sp = opADDImmediate(_sp);						break;
	case 0xE9:	_pc = _hl;										break;
	case 0xEA: _mmu->Write(_mmu->ReadWord(_pc++));				break;
	// case 0xEB:													break;
	// case 0xEC:													break;
	// case 0xED:													break;
	case 0xEE: opXOR(_mmu->Read(_pc++));						break;
	case 0xEF: ResetVector(0x28);


	case 0xF0: A() = _mmu->Read(0xFF00 + _mmu->ReadWord(_pc++));	break;
	case 0xF1: _af = StackPop();									break;
	case 0xF2: A() = _mmu->Read(0xFF00 + C());						break;
	case 0xF3: IME = false;											break;
	// case 0xF4:														break;
	case 0xF5: StackPush(_af);										break;
	case 0xF6: opOR(_mmu->Read(_pc++));								break;
	case 0xF7: ResetVector(0x30);									break;

	case 0xF8:;
	case 0xF9:;
	case 0xFA:;
	case 0xFB:;
	case 0xFC:;
	case 0xFD:;
	case 0xFE:;
	case 0xFF:;
	}
}