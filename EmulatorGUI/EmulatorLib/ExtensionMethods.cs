using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EmulatorGUI.EmulatorLib
{
    public static class ExtensionMethods
    {
        public static string ToString(this OperandType type)
        {
            switch (type)
            {
                case OperandType.None:
                    return string.Empty;
                case OperandType.Acculumator:
                    return "A";
                case OperandType.RegisterB:
                    return "B";
                case OperandType.RegisterC:
                    return "C";
                case OperandType.RegisterD:
                    return "D";
                case OperandType.RegisterE:
                    return "E";
                case OperandType.RegisterH:
                    return "H";
                case OperandType.RegisterL:
                    return "L";
                case OperandType.RegisterAF:
                    return "AF";
                case OperandType.RegisterBC:
                    return "BC";
                case OperandType.RegisterDE:
                    return "DE";
                case OperandType.RegisterHL:
                    return "HL";
                case OperandType.Stackpointer:
                    return "SP";
                case OperandType.ProgramCounter:
                    return "PC";
                case OperandType.IncrementHL:
                    return "[HL++]";
                case OperandType.DecrementHL:
                    return "[HL--]";
                case OperandType.RegisterCIndirect:
                    return "[C]";
                case OperandType.RegisterBCIndirect:
                    return "[BC]";
                case OperandType.RegisterDEIndirect:
                    return "[DE]";
                case OperandType.RegisterHLIndirect:
                    return "[HL]";
                case OperandType.DataUINT8:
                    return "d8";
                case OperandType.AddressUINT8:
                    return "u8";
                case OperandType.DataUINT16:
                    return "d16"; 
                case OperandType.AddressUINT16:
                    return "a16";
                case OperandType.FlagCarry:
                    return "c";
                case OperandType.FlagHalfCarry:
                    return "h";
                case OperandType.FlagNegative:
                    return "s";
                case OperandType.FlagZero:
                    return "z";
                case OperandType.FlagNotCarry:
                    return "nc";
                case OperandType.FlagNotHalfCarry:
                    return "nh";
                case OperandType.FlagNotNegative:
                    return "ns";
                case OperandType.FlagNotZero:
                    return "nz";
            }
            return string.Empty;
        }

    }
}
