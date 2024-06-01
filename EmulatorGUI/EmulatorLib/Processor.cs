using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace EmulatorGUI.EmulatorLib
{
    public class Processor : IDisposable
    {
        [DllImport("EmulatorLib.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern nint processor_create();

        [DllImport("EmulatorLib.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void processor_delete(nint pointer);


        nint _cpointer = nint.Zero;

        public Processor()
        {
            _cpointer = processor_create();
        }

        public void Dispose()
        {
            if (_cpointer != nint.Zero)
                processor_delete(_cpointer);
        }
    }
}
