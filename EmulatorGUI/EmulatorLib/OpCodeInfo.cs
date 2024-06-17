using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Reflection.Emit;
using System.ComponentModel;
using EmulatorGUI.EmulatorLib;

namespace EmulatorGUI.EmulatorLib
{
    public enum OpCode
    {
		// Misc Instructions
		NOP,
		STOP,
		HALT,
		PREFIX,
		DI,
		EI,

		// Jump
		JR,
		RET,
		JP,
		CALL,
		RST,
		RETI,

		// SHARED 8/16 bit load/move/store instuctions
		LD,

		// 8 Bit load/move/store Instructions 
		// LD_8,
		LDH,

		// 16 bit load/move/store Instructions
		// LD_16,
		POP,
		PUSH,

		// SHARED 8/16 bit arithmetic/logical Instructions 
		INC,
		DEC,
		ADD,

		// 8 Bit arithmetic/logical Instructions 
		// INC_8,
		// DEC,
		DAA,
		SCF,
		CPL,
		CCF,
		// ADD,
		ADC,
		SUB,
		SBC,
		AND,
		XOR,
		OR,
		CP,

		// 8 Bit rotations/shifts and bit Instructions
		RLCA,
		RRCA,
		RLA,
		RRA,
		RLC,
		RRC,
		RL,
		RR,
		SLA,
		SRA,
		SWAP,
		SRL,
		BIT,
		RES,
		SET,


		XXX
	};

	/// <summary>
	/// Type defining all possible "inputs" and "outputs" of an instruction
	/// </summary>
	public enum OperandType
	{
		None,

		Acculumator,
		RegisterB,
		RegisterC,
		RegisterD,
		RegisterE,
		RegisterH,
		RegisterL,

		RegisterAF,
		RegisterBC,
		RegisterDE,
		RegisterHL,
		Stackpointer,
		ProgramCounter,

		IncrementHL,
		DecrementHL,

		RegisterCIndirect,

		RegisterBCIndirect,
		RegisterDEIndirect,
		RegisterHLIndirect,

		DataUINT8,
		DataUINT16,

		AddressUINT8,
		AddressUINT16,

		DataINT8,

		FlagCarry,
		FlagHalfCarry,
		FlagNegative,
		FlagZero,

		FlagNotCarry,
		FlagNotHalfCarry,
		FlagNotNegative,
		FlagNotZero,
	};

    public partial struct OpCodeInfo
	{
		[LibraryImport("EmulatorLib.dll")]
		[UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
		private static partial byte opcode_getopcode(byte value);

		[LibraryImport("EmulatorLib.dll")]
		[UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
		private static partial byte opcode_getprefixopcode(byte value);
		[LibraryImport("EmulatorLib.dll")]
		[UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
		private static partial byte opcode_getlhsoperand(byte value);
		[LibraryImport("EmulatorLib.dll")]
		[UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
		private static partial byte opcode_getrhsoperand(byte value);

		[LibraryImport("EmulatorLib.dll")]
		[UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
		private static partial byte opcode_getprefixlhsoperand(byte value);

		[LibraryImport("EmulatorLib.dll")]
		[UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
		private static partial byte opcode_getprefixrhsoperand(byte value);

		public OpCodeInfo()
		{
			OpCode = OpCode.NOP;
			LeftHandOperand = OperandType.None;
			RightHandOperand = OperandType.None;
		}

		public OpCodeInfo(OpCode opcode, OperandType lhsOperand, OperandType rhsOperandType)
		{
			OpCode = opcode;
			LeftHandOperand = lhsOperand;
			RightHandOperand = rhsOperandType;
		}

		public OpCode OpCode { get; private set; }
		public OperandType LeftHandOperand { get; private set; }
		public OperandType RightHandOperand { get; private set; }


		public static OpCodeInfo GetOpCodeInfo(byte index) => new((OpCode)opcode_getopcode(index), (OperandType)opcode_getlhsoperand(index), (OperandType)opcode_getrhsoperand(index));
        public static OpCodeInfo GetOpCodePrefixedInfo(byte index) => new((OpCode)opcode_getprefixopcode(index), (OperandType)opcode_getprefixlhsoperand(index), (OperandType)opcode_getprefixrhsoperand(index));


        public new string ToString()
        {
			if (LeftHandOperand == OperandType.None && RightHandOperand == OperandType.None)
				return OpCode.ToString();
			else if (LeftHandOperand == OperandType.None && RightHandOperand != OperandType.None)
				return $"{OpCode} {ExtensionMethods.ToString(RightHandOperand)}";
			else if (LeftHandOperand != OperandType.None && RightHandOperand == OperandType.None)
				return $"{OpCode} {ExtensionMethods.ToString(LeftHandOperand)}";
			else
				return $"{OpCode} {ExtensionMethods.ToString(LeftHandOperand)}, {ExtensionMethods.ToString(RightHandOperand)}";
        }
    }
}
