using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace EmulatorGUI.EmulatorLib
{
    public partial class MemoryBus : ObjectBase
    {

        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial nint memorybus_create(nint rompointer);


        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial void memorybus_randomize(nint pointer);

        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial void memorybus_write(nint pointer, ushort address, byte value);

        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial byte memorybus_read(nint pointer, ushort address);

        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial byte memorybus_isaddressmapped(nint pointer, ushort address);

        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial byte memorybus_writerom(in nint pointer, in byte[] data, in ushort length);



        public MemoryBus(RomInfo romInfo) : base(memorybus_create(romInfo.CPointer))
        {

        }

        public override void Destroy()
        {

        }


        public void Randomize() => memorybus_randomize(CPointer);
        public bool IsAddressMapped(ushort address) => memorybus_isaddressmapped(CPointer, address) != 0;
        public void Write(ushort address, byte value) => memorybus_write(CPointer, address, value);
        public byte Read(ushort address) => memorybus_read(CPointer, address);

        public void WriteROM(byte[] data) => memorybus_writerom(CPointer, data, (ushort)data.Length);
    }
}
