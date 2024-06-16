ECHO Copying Unmanaged Libraries
ECHO Copy SRC: %1\build\x64\%2\EmulatorLib.*
ECHO COPY DST: %1\EmulatorGUI\bin\%2\net8.0-windows\

XCOPY %1\build\x64\%2\EmulatorLib.* %1\EmulatorGUI\bin\%2\net8.0-windows\ /y