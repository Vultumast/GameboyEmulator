using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EmulatorGUI
{
    public class EmulationConfiguration
    {
        public SystemConfiguration GameboyConfiguration { get; set; } = new SystemConfiguration();
        public SystemConfiguration GameboyColorConfiguration { get; set; } = new SystemConfiguration();
    }
}
