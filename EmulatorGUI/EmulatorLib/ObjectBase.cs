using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace EmulatorGUI.EmulatorLib
{
    public abstract partial class ObjectBase : IDisposable
    {
        private nint _cPointer = nint.Zero;
        private bool disposedValue;

        public nint CPointer => _cPointer;

        [LibraryImport("EmulatorLib.dll")]
        [UnmanagedCallConv(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
        private static partial void pointer_delete(in nint pointer);


        protected virtual void Dispose(bool disposing)
        {
            if (!disposedValue)
            {
                if (disposing)
                {
                    // TODO: dispose managed state (managed objects)
                }

                if (_cPointer != nint.Zero)
                {
                    pointer_delete(_cPointer);
                    Destroy();
                }

                _cPointer = nint.Zero;
                disposedValue = true;
            }
        }
        protected ObjectBase(nint cPointer)
        {
            _cPointer = cPointer;
        }

        ~ObjectBase()
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

        public abstract void Destroy();
    }
}
