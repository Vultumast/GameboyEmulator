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
        A,
        B,
        C,
        D,
        E,
        H,
        L,

        AF,
        BC,
        DE,
        HL,
        SP,
        PC
    };
    public partial class Processor : ObjectBase
    {
        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial nint processor_create(nint memoryBus);
        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial void processor_reset(nint processor);

        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial void processor_setregister(nint processor, byte register, ushort value);
        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial ushort processor_getregister(nint processor, byte register);

        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial void processor_pulseclock(nint processor);

        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial byte processor_getremainingcycles(nint processor);

        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial byte processor_getinterruptsenabled(nint processor);
        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial void processor_setinterruptsenabled(nint processor, byte value);

        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial byte processor_getflag(nint processor, byte flag);
        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial void processor_setflag(nint processor, byte flag, byte value);

        public enum Flags
        {
            C = (1 << 4),
            H = (1 << 5),
            N = (1 << 6),
            Z = (1 << 7),
        };


        public Processor(MemoryBus memoryBus) : base(processor_create(memoryBus.CPointer))
        {

        }

        public override void Destroy()
        {

        }
        public void Reset() => processor_reset(CPointer);

        public void SetRegister(Register register, ushort value) => processor_setregister(CPointer, (byte)register, value);
        public ushort GetRegister(Register register) => processor_getregister(CPointer, (byte)register);

        public void PulseClock() => processor_pulseclock(CPointer);

        /// <summary>
        /// Pulses the clock until the current instruction timer reaches 0
        /// </summary>
        public void ConsumeInstruction()
        {
            while (RemainingCycles != 0)
                PulseClock();
            PulseClock();
        }

        public byte RemainingCycles => processor_getremainingcycles(CPointer);

        public bool InterruptsMasterEnabled
        {
            get => processor_getinterruptsenabled(CPointer) == 1;
            set => processor_setinterruptsenabled(CPointer, (byte)(value ? 1 : 0));
        }

        public void SetFlag(Flags flag, bool value) => processor_setflag(CPointer, (byte)flag, (byte)(value ? 1 : 0));
        public bool GetFlag(Flags flag) => processor_getflag(CPointer, (byte)flag) == 1;
    }
}
