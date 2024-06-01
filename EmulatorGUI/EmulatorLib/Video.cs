using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace EmulatorGUI.EmulatorLib
{
    public class Video : ObjectBase
    {
        [DllImport("EmulatorLib.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern nint video_create();

        [DllImport("EmulatorLib.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void video_delete(nint pointer);

        public Video() : base(video_create())
        {

        }

        public override void Destroy()
        {
            video_delete(CPointer);
        }
    }
}
