using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace EmulatorGUI.EmulatorLib
{
    public partial class Video : ObjectBase
    {
        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial nint video_create(nint memorybus, nint hwnd);


        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial void video_clear(nint pointer);

        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial void video_present(nint pointer);

        public Video(MemoryBus memoryBus, nint WindowHandle) : base(video_create(memoryBus.CPointer, WindowHandle))
        {

        }

        public override void Destroy()
        {

        }

        public void Clear() => video_clear(CPointer);
        public void Present() => video_present(CPointer);
    }
}
