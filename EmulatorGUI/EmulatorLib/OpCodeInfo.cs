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

		FlagCarry,
		FlagHalfCarry,
		FlagNegative,
		FlagZero,

		FlagNotCarry,
		FlagNotHalfCarry,
		FlagNotNegative,
		FlagNotZero,
	};



    enum Registers8Bit
    {
        B,
        C,
        D,
        E,
        H,
        L,
        HL_Indirect,
        A,
    }

    enum Registers16Bit1
    {
        BC,
        DE,
        HL,
        SP
    }
    enum Registers16Bit2
    {
        BC,
        DE,
        HL,
        AF
    }

    enum Conditions
    {
        NZ,
        Z,
        NC,
        C
    }


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

		public OpCodeInfo(byte hexCode)
		{
			byte z = (byte)(hexCode & 0b00000111);
			byte y = (byte)((hexCode & 0b00111000) >> 3);
			byte x = (byte)((hexCode & 0b11000000) >> 5);

			OpCode _opCode = OpCode.NOP;


            switch (x)
			{
				case 0:
					parseCategory0();
                    break;
				case 1:
                    parseCategory1();
                    break;
				case 2:
                    parseCategory2();
                    break;
				case 3:
                    parseCategory3();
                    break;
			}

			OpCode = _opCode;
			return;

			void parseCategory0()
			{
				switch (z)
				{
					case 0: // Relative jumps and assorted ops
						switch (y)
						{
							case 0:
                                _opCode = OpCode.NOP;
                                break;
							case 1:
		
								break;
							case 2:
								break;
							case 3:
								break;
							case 4:
								break;
						}

						break;
                    case 1: // 16-bit load immediate/add
                        break;
                    case 2: // Indirect loading
                        break;
                    case 3: // 16-bit INC/DEC
                        break;
                    case 4: // 8-bit INC
                        break;
                    case 5: // 8-bit DEC
                        break;
                    case 6: // 8-bit load immediate
                        break;
                    case 7: // Assorted operations on accumulator/flags
                        break;
                }

			}

			void parseCategory1()
            {

            }

            void parseCategory2()
            {

            }

            void parseCategory3()
            {

            }
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
