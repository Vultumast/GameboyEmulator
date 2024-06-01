using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EmulatorGUI.EmulatorLib
{
    public abstract class ObjectBase : IDisposable
    {
        private nint _cPointer = nint.Zero;
        private bool disposedValue;

        public nint CPointer => _cPointer;

        protected virtual void Dispose(bool disposing)
        {
            if (!disposedValue)
            {
                if (disposing)
                {
                    // TODO: dispose managed state (managed objects)
                }

                if (_cPointer != nint.Zero)
                    Destroy();

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
