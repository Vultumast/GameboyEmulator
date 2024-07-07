#pragma once

#include "Constants.hpp"

class MemoryBus;

using namespace std;

namespace kitsemu
{
	constexpr uint8_t JUMP_CYCLES[2] = { 12, 16 };
	constexpr uint8_t JUMP_RELATIVE_CYCLES[2] = { 8, 12 };
	constexpr uint8_t RETURN_CYCLES[2] = { 8, 20 };
	constexpr uint8_t CALL_CYCLES[2] = { 12, 24 };

	class CPU
	{
	private:
		MemoryBus* _mmu = nullptr;

		uint8_t _cycles = 0;

		uint16_t _pc = 0;
		uint16_t _sp = 0;

		uint16_t _af = 0;
		uint16_t _bc = 0;
		uint16_t _de = 0;
		uint16_t _hl = 0;

		// 8-bit OpCodes
		uint8_t opINC(uint8_t reg);
		uint8_t opDEC(uint8_t reg);
		void opRLCA();
		void opADDReg(uint16_t reg);
		void opRRCA();
		void opSTOP();
		void opRLA();
		void opRRA();
		void opJR(bool condition);
		void opDAA();
		void opCPL();
		void opSCF();
		void opCCF();
		void opHALT();
		void opADD(uint8_t value);
		void opADC(uint8_t value);
		void opSUB(uint8_t value);
		void opSBC(uint8_t value);
		void opAND(uint8_t value);
		void opXOR(uint8_t value);
		void opOR(uint8_t value);
		void opCP(uint8_t value);
		void opRT(bool condition);
		void opJP(bool condition);
		void opCALL(bool condition);
		void opPREFIX(uint8_t opcode);
		uint16_t opADDImmediate(uint8_t value);

		// 16-bit OpCodes

		uint8_t opRLC(uint8_t byte);
		uint8_t opRRC(uint8_t byte);
		uint8_t opRL(uint8_t byte);
		uint8_t opRR(uint8_t byte);
		uint8_t opSLA(uint8_t byte);
		uint8_t opSRA(uint8_t byte);
		uint8_t opSWAP(uint8_t byte);
		uint8_t opSRL(uint8_t byte);

		uint8_t opSET(uint8_t byte, uint8_t reg);
		uint8_t opRES(uint8_t byte, uint8_t reg);
		void opBIT(uint8_t byte, uint8_t reg);
	public:

		enum Flag : uint8_t
		{
			Z = 0x80,
			N = 0x40,
			H = 0x20,
			C = 0x10
		};

		CPU(MemoryBus& mmu);

		/// <summary>
		/// Executes at the location of the Program Counter
		/// </summary>
		void Execute();

		void Reset();

		/// <summary>
		/// Sets the registers to the state they would have if the boot rom had finished successfully.
		/// </summary>
		void SetDefaultRegisters();

		/// <summary>
		/// Are interrupts enabled?
		/// </summary>
		bool IME = false;

		/// <summary>
		/// Should execution be stopped until an interrupt occurs?
		/// </summary>
		bool Halted = false;

		/// <summary>
		/// Should execution be stopped?
		/// </summary>
		bool Stopped = false;

		/// <summary>
		/// The Program Counter
		/// </summary>
		/// <returns></returns>
		uint16_t& PC() { return _pc; }
		/// <summary>
		/// The Stackpointer
		/// </summary>
		/// <returns></returns>
		uint16_t& SP() { return _sp; }
		/// <summary>
		/// The AF register
		/// </summary>
		/// <returns></returns>
		uint16_t& AF() { return _af; }
		/// <summary>
		/// The BC register
		/// </summary>
		/// <returns></returns>
		uint16_t& BC() { return _bc; }
		/// <summary>
		/// The DE register
		/// </summary>
		/// <returns></returns>
		uint16_t& DE() { return _de; }
		/// <summary>
		/// The HL register
		/// </summary>
		/// <returns></returns>
		uint16_t& HL() { return _hl; }
		/// <summary>
		/// The A register (or Accumulator)
		/// </summary>
		/// <returns></returns>
		uint8_t& A() 
		{
			uint8_t* ptr = (reinterpret_cast<uint8_t*>(&_af) + 1);
			return reinterpret_cast<uint8_t&>(ptr);
		}
		/// <summary>
		/// The B register
		/// </summary>
		/// <returns></returns>
		uint8_t& B()
		{
			uint8_t* ptr = (reinterpret_cast<uint8_t*>(&_bc) + 1);
			return reinterpret_cast<uint8_t&>(ptr);
		}
		/// <summary>
		/// The C register
		/// </summary>
		/// <returns></returns>
		uint8_t& C()
		{
			uint8_t* ptr = reinterpret_cast<uint8_t*>(&_bc);
			return reinterpret_cast<uint8_t&>(ptr);
		}
		/// <summary>
		/// The D register
		/// </summary>
		/// <returns></returns>
		uint8_t& D()
		{
			uint8_t* ptr = (reinterpret_cast<uint8_t*>(&_de) + 1);
			return reinterpret_cast<uint8_t&>(ptr);
		}
		/// <summary>
		/// The E register
		/// </summary>
		/// <returns></returns>
		uint8_t& E()
		{
			uint8_t* ptr = reinterpret_cast<uint8_t*>(&_de);
			return reinterpret_cast<uint8_t&>(ptr);
		}
		/// <summary>
		/// The H register
		/// </summary>
		/// <returns></returns>
		uint8_t& H()
		{
			uint8_t* ptr = (reinterpret_cast<uint8_t*>(&_hl) + 1);
			return reinterpret_cast<uint8_t&>(ptr);
		}
		/// <summary>
		/// The L register
		/// </summary>
		/// <returns></returns>
		uint8_t& L()
		{
			uint8_t* ptr = reinterpret_cast<uint8_t*>(&_hl);
			return reinterpret_cast<uint8_t&>(ptr);
		}

		bool SetFlag(Flag flag, bool value)
		{
			if (value)
				_af |= flag;
			else
				_af &= (0xFF00 | ~flag);
		}
		bool GetFlag(Flag flag) const { return (_af & flag) != 0; }

		void ClearFlags() { _af &= 0xFF00; };

		bool GetFlagZ() const { return (_af & Flag::Z) != 0; }
		bool GetFlagN() const { return (_af & Flag::N) != 0; }
		bool GetFlagH() const { return (_af & Flag::H) != 0; }
		bool GetFlagC() const { return (_af & Flag::C) != 0; }

		uint16_t StackPop()
		{
			uint16_t returnValue = _mmu->ReadWord(_sp);
			_sp += 2;
			return returnValue;
		}
		void StackPush(uint16_t value)
		{
			_sp -= 2;
			_mmu->WriteWord(_sp, value);
		}

		void ResetVector(uint8_t address)
		{
			StackPush(_pc);
			_pc = address;
		}
	};
}