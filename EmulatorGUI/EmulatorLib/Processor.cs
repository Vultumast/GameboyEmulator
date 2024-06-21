using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Diagnostics;
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

        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial void processor_consumeinstruction(nint processor);


        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial void do_the_thing(nint processor, nint video);
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

        /// <summary>
        /// The A register
        /// </summary>
        public byte A
        {
            get => (byte)processor_getregister(CPointer, (byte)Register.A);
            set => processor_setregister(CPointer, (byte)Register.A, value);
        }

        /// <summary>
        /// The PC register
        /// </summary>
        public ushort PC
        {
            get => processor_getregister(CPointer, (byte)Register.PC);
            set => processor_setregister(CPointer, (byte)Register.PC, value);
        }

        /// <summary>
        /// The SP register
        /// </summary>
        public ushort SP
        {
            get => processor_getregister(CPointer, (byte)Register.SP);
            set => processor_setregister(CPointer, (byte)Register.SP, value);
        }


        public void PulseClock() => processor_pulseclock(CPointer);

        /// <summary>
        /// Pulses the clock until the current instruction timer reaches 0
        /// </summary>
        public void ConsumeInstruction() => processor_consumeinstruction(CPointer);
        /*{

        loopStart:
            PulseClock();
            if (RemainingCycles != 0)
                goto loopStart;

            PulseClock();
        } */

        public byte RemainingCycles => processor_getremainingcycles(CPointer);

        public bool InterruptsMasterEnabled
        {
            get => processor_getinterruptsenabled(CPointer) == 1;
            set => processor_setinterruptsenabled(CPointer, (byte)(value ? 1 : 0));
        }

        public void SetFlag(Flags flag, bool value) => processor_setflag(CPointer, (byte)flag, (byte)(value ? 1 : 0));
        public bool GetFlag(Flags flag) => processor_getflag(CPointer, (byte)flag) == 1;


        public void theThing(Video video)
        {
            do_the_thing(CPointer, video.CPointer);
        }
    }
}
