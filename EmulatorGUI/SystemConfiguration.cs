using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EmulatorGUI
{
    public enum EchoRAMBehavior
    {
        Mirror,
        Expansion,
        Forced
    }
    public struct SystemConfiguration
    {
        public SystemConfiguration()
        {

        }

        public SystemConfiguration(ref SystemConfiguration source)
        {
            BootROMFilepath = source.BootROMFilepath;
            RandomizeRAM = source.RandomizeRAM;
            EchoRAMBehavior = source.EchoRAMBehavior;
            EchoRAMForcedValue = source.EchoRAMForcedValue;
        }

        public string BootROMFilepath { get; set; } = string.Empty;
        public bool RandomizeRAM { get; set; } = true;

        public EchoRAMBehavior EchoRAMBehavior { get; set; } = EchoRAMBehavior.Mirror;
        public byte EchoRAMForcedValue { get; set; } = 0x00;
    }
}
