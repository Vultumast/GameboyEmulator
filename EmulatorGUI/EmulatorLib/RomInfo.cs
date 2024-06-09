using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace EmulatorGUI.EmulatorLib
{
	public enum CartridgeType
	{
		ROM_Only = 0x00,
		MBC1,
		MBC1_RAM,
		MBC1_RAM_BATTERY,

		MBC2 = 0x05,
		MBC2_RAM,

		ROM_RAM = 0x08,
		ROM_RAM_BATTERY,

		MMM01 = 0x0B,
		MMM01_RAM,
		MMM01_RAM_BATTERY,

		MBC3_TIMER_BATTERY = 0x0F,
		MBC3_TIMER_RAM_BATTERY,
		MBC3,
		MBC3_RAM,
		MBC3_RAM_BATTERY,

		MBC5 = 0x19,
		MBC5_RAM = 0x1A,
		MBC5_RAM_BATTERY,
		MBC5_RUMBLE,
		MBC5_RUMBLE_RAM,
		MBC5_RUMBLE_RAM_BATTERY,

		MBC6 = 0x20,

		MBC7_SENSOR_RUMBLE_RAM_BATTERY = 0x22,

		POCKET_CAMERA = 0xFC,
		BANDAI_TAMA5 = 0xFD,
		HuC3 = 0xFE,
		HuC1_RAM_BATTERY = 0xFF
	};

    public enum MapperType
	{
		None,
		MBC1,
		MBC2,
		MBC3,
		MBC5,
		MBC6,
		MBC7,
		MMM01,
		HuC1,
		HuC3,
		TAMA5
	};

	public partial class RomInfo : ObjectBase
    {
        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial nint rominfo_create(byte[] data, int size);

        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial byte rominfo_getcartridgetype(nint pointer);
        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial byte rominfo_getmappertype(nint pointer);
        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial uint rominfo_getramsize(nint pointer);

        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial byte rominfo_read(nint pointer, uint address);

        public RomInfo(byte[] data) : base(rominfo_create(data, data.Length))
        {

        }


        public string GameName { get; private set; } = string.Empty;

		public byte Revision { get; private set; } = 0;

		public byte RawCartridgeType => (byte)CartridgeType;

		public CartridgeType CartridgeType => (CartridgeType)rominfo_getcartridgetype(CPointer);



        public MapperType MapperType => (MapperType)rominfo_getmappertype(CPointer);
		public bool HasRAM()
		{
            return CartridgeType switch
            {
                CartridgeType.MBC1_RAM or CartridgeType.MBC1_RAM_BATTERY or CartridgeType.MBC2_RAM or CartridgeType.ROM_RAM or CartridgeType.ROM_RAM_BATTERY or CartridgeType.MMM01_RAM or CartridgeType.MMM01_RAM_BATTERY or CartridgeType.MBC3_TIMER_RAM_BATTERY or CartridgeType.MBC3_RAM or CartridgeType.MBC3_RAM_BATTERY or CartridgeType.MBC5_RAM or CartridgeType.MBC5_RAM_BATTERY or CartridgeType.MBC5_RUMBLE_RAM_BATTERY or CartridgeType.MBC7_SENSOR_RUMBLE_RAM_BATTERY or CartridgeType.HuC1_RAM_BATTERY => true,
                _ => false,
            };
        }
		public bool HasBattery()
		{
            return CartridgeType switch
            {
                CartridgeType.MBC1_RAM_BATTERY or CartridgeType.ROM_RAM_BATTERY or CartridgeType.MMM01_RAM_BATTERY or CartridgeType.MBC3_TIMER_BATTERY or CartridgeType.MBC3_TIMER_RAM_BATTERY or CartridgeType.MBC3_RAM_BATTERY or CartridgeType.MBC5_RUMBLE_RAM_BATTERY or CartridgeType.MBC7_SENSOR_RUMBLE_RAM_BATTERY or CartridgeType.HuC1_RAM_BATTERY => true,
                _ => false,
            };
        }
		public bool HasRumble()
		{
            return CartridgeType switch
            {
                CartridgeType.MBC5_RUMBLE or CartridgeType.MBC5_RUMBLE_RAM or CartridgeType.MBC5_RUMBLE_RAM_BATTERY or CartridgeType.MBC7_SENSOR_RUMBLE_RAM_BATTERY => true,
                _ => false,
            };
        }

        public override void Destroy()
        {

        }

        public int ROMSize { get; private set; } = 0;
		public uint RAMSize => rominfo_getramsize(CPointer);

        public int BankCount => ROMSize / 16000;

		public byte Read(uint address) => rominfo_read(CPointer, address);
    }
}
