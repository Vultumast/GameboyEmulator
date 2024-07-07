using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace EmulatorGUI.EmulatorLib
{
    public enum Register
    {
        AF,
        BC,
        DE,
        HL,
        SP,
        PC,
        A,
        B,
        C,
        D,
        E,
        H,
        L
    }
    public partial class CPU : ObjectBase
    { 

        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial nint cpu_create(nint memorybuspointer);

        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial ushort cpu_getregister(nint pointer, byte register);

        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial void cpu_setregister(nint pointer, byte register, ushort value);

        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial byte cpu_getcycles(nint pointer);

        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial byte cpu_execute(nint pointer);

        public CPU(MemoryBus bus) : base(cpu_create(bus.CPointer))
        {

        }
        public override void Destroy()
        {

        }
        public void Execute() => cpu_execute(CPointer);

        public byte Cycles => cpu_getcycles(CPointer);
        #region Registers
        public void SetRegister(Register register, ushort value) => cpu_setregister(CPointer, (byte)register, value);
        public ushort GetRegister(Register register) => cpu_getregister(CPointer, (byte)register);

        public ushort AF
        {
            get => cpu_getregister(CPointer, (byte)Register.AF);
            set => cpu_setregister(CPointer, (byte)Register.AF, value);
        }
        public ushort BC
        {
            get => cpu_getregister(CPointer, (byte)Register.BC);
            set => cpu_setregister(CPointer, (byte)Register.BC, value);
        }
        public ushort DE
        {
            get => cpu_getregister(CPointer, (byte)Register.DE);
            set => cpu_setregister(CPointer, (byte)Register.DE, value);
        }
        public ushort HL
        {
            get => cpu_getregister(CPointer, (byte)Register.HL);
            set => cpu_setregister(CPointer, (byte)Register.HL, value);
        }
        public ushort SP
        {
            get => cpu_getregister(CPointer, (byte)Register.SP);
            set => cpu_setregister(CPointer, (byte)Register.SP, value);
        }
        public ushort PC
        {
            get => cpu_getregister(CPointer, (byte)Register.PC);
            set => cpu_setregister(CPointer, (byte)Register.PC, value);
        }
        public ushort A
        {
            get => cpu_getregister(CPointer, (byte)Register.A);
            set => cpu_setregister(CPointer, (byte)Register.A, value);
        }
        public ushort B
        {
            get => cpu_getregister(CPointer, (byte)Register.B);
            set => cpu_setregister(CPointer, (byte)Register.B, value);
        }
        public ushort C
        {
            get => cpu_getregister(CPointer, (byte)Register.C);
            set => cpu_setregister(CPointer, (byte)Register.C, value);
        }
        public ushort D
        {
            get => cpu_getregister(CPointer, (byte)Register.D);
            set => cpu_setregister(CPointer, (byte)Register.D, value);
        }
        public ushort E
        {
            get => cpu_getregister(CPointer, (byte)Register.E);
            set => cpu_setregister(CPointer, (byte)Register.E, value);
        }
        public ushort H
        {
            get => cpu_getregister(CPointer, (byte)Register.H);
            set => cpu_setregister(CPointer, (byte)Register.H, value);
        }
        public ushort L
        {
            get => cpu_getregister(CPointer, (byte)Register.L);
            set => cpu_setregister(CPointer, (byte)Register.L, value);
        }
        #endregion

    }
}
