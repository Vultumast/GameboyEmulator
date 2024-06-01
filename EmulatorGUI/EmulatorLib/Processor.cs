﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace EmulatorGUI.EmulatorLib
{
    public class Processor : ObjectBase
    {
        [DllImport("EmulatorLib.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern nint processor_create();

        [DllImport("EmulatorLib.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void processor_delete(nint pointer);

        public Processor() : base(processor_create())
        {

        }

        public override void Destroy()
        {
            processor_delete(CPointer);
        }
    }
}
