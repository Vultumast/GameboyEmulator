using System;
using System.Collections.Generic;
using System.Linq;
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

	public class RomInfo
    {
        public RomInfo(MemoryBus memoryBus)
		{
			for (ushort i = 0x134; i < 0x0143; i++)
			{
				char c = (char)memoryBus.Read(i);
				if (c == '\0')
					break;
				GameName += c;
			}

			RawCartridgeType = memoryBus.Read(0x147);
			ROMSize = 32000 << memoryBus.Read(0x148);
			switch (memoryBus.Read(0x149))
			{
				case 0x00:
				default:
					RAMSize = 0;
					break;
				case 0x02:
					RAMSize = 8000;
                    break;
                case 0x03:
                    RAMSize = 32000;
                    break;
                case 0x04:
                    RAMSize = 128000;
                    break;
                case 0x05:
                    RAMSize = 64000;
                    break;
            }

			Revision = memoryBus.Read(0x14C);
        }
        public RomInfo(byte[] data)
        {
            for (ushort i = 0x134; i < 0x0143; i++)
            {
                char c = (char)data[i];
                if (c == '\0')
                    break;
                GameName += c;
            }

            RawCartridgeType = data[0x147];
            ROMSize = 32000 << data[0x148];
            switch (data[0x149])
            {
                case 0x00:
                default:
                    RAMSize = 0;
                    break;
                case 0x02:
                    RAMSize = 8000;
                    break;
                case 0x03:
                    RAMSize = 32000;
                    break;
                case 0x04:
                    RAMSize = 128000;
                    break;
                case 0x05:
                    RAMSize = 64000;
                    break;
            }

            Revision = data[0x14C];
        }

        public string GameName { get; private set; } = string.Empty;

		public byte Revision { get; private set; } = 0;

		public byte RawCartridgeType { get; private set; } = 0;

		public CartridgeType CartridgeType => (CartridgeType)RawCartridgeType;



        public MapperType MapperType
		{
			get
			{
                return CartridgeType switch
                {
                    CartridgeType.MBC1 or CartridgeType.MBC1_RAM or CartridgeType.MBC1_RAM_BATTERY => MapperType.MBC1,
                    CartridgeType.MBC2 or CartridgeType.MBC2_RAM => MapperType.MBC2,
                    CartridgeType.MMM01 or CartridgeType.MMM01_RAM or CartridgeType.MMM01_RAM_BATTERY => MapperType.MMM01,
                    CartridgeType.MBC3_TIMER_BATTERY or CartridgeType.MBC3_TIMER_RAM_BATTERY or CartridgeType.MBC3 or CartridgeType.MBC3_RAM or CartridgeType.MBC3_RAM_BATTERY => MapperType.MBC3,
                    CartridgeType.MBC5 or CartridgeType.MBC5_RAM or CartridgeType.MBC5_RAM_BATTERY or CartridgeType.MBC5_RUMBLE or CartridgeType.MBC5_RUMBLE_RAM or CartridgeType.MBC5_RUMBLE_RAM_BATTERY => MapperType.MBC5,
                    CartridgeType.MBC6 => MapperType.MBC6,
                    CartridgeType.MBC7_SENSOR_RUMBLE_RAM_BATTERY => MapperType.MBC7,
                    CartridgeType.BANDAI_TAMA5 => MapperType.TAMA5,
                    CartridgeType.HuC1_RAM_BATTERY => MapperType.HuC1,
                    CartridgeType.HuC3 => MapperType.HuC3,
                    _ => MapperType.None,
                };
            }
		}
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

		public int ROMSize { get; private set; } = 0;
        public int RAMSize { get; private set; } = 0;

        public int BankCount => ROMSize / 16000;

    }
}
