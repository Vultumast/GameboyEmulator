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
        public static extern nint video_create(nint memorybus, nint hwnd);

        [DllImport("EmulatorLib.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void video_delete(nint pointer);

        [DllImport("EmulatorLib.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void video_clear(nint pointer);

        [DllImport("EmulatorLib.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void video_present(nint pointer);

        public Video(MemoryBus memoryBus, nint WindowHandle) : base(video_create(memoryBus.CPointer, WindowHandle))
        {

        }

        public override void Destroy()
        {
            video_delete(CPointer);
        }

        public void Clear() => video_clear(CPointer);
        public void Present() => video_present(CPointer);
    }
}
