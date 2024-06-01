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
        private bool disposedValue;

        public Processor()
        {
            _cpointer = processor_create();
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!disposedValue)
            {
                if (disposing)
                {
                    // TODO: dispose managed state (managed objects)
                }
                if (_cpointer != nint.Zero)
                    processor_delete(_cpointer);
                disposedValue = true;
            }
        }

        // // TODO: override finalizer only if 'Dispose(bool disposing)' has code to free unmanaged resources
        ~Processor()
        {
            // Do not change this code. Put cleanup code in 'Dispose(bool disposing)' method
            Dispose(disposing: false);
        }

        public void Dispose()
        {
            // Do not change this code. Put cleanup code in 'Dispose(bool disposing)' method
            Dispose(disposing: true);
            GC.SuppressFinalize(this);
        }
    }
}
