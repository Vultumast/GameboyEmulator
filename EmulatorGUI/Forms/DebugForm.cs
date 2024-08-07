using EmulatorGUI.EmulatorLib;
using System.Diagnostics;
using System.Drawing;
using System.Reflection.Metadata.Ecma335;

namespace EmulatorGUI
{
    public partial class DebugForm : Form
    {
        public DebugForm()
        {
            InitializeComponent();
            typeof(Panel)
                .GetProperty("DoubleBuffered", System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance)
                ?.GetSetMethod(true)
                ?.Invoke(rawPanel, new object[] { true });
        }
        RomInfo? info = null;

        MemoryBus? bus = null;
        CPU? cpu = null;
        Video? video = null;


        private void button1_Click(object sender, EventArgs e)
        {
            // info = new RomInfo(File.ReadAllBytes("rom.gb"));
            // info = new RomInfo(File.ReadAllBytes("Tetris.gb"));
            // info = new RomInfo(File.ReadAllBytes("alleyway.gb
            info = new RomInfo(File.ReadAllBytes("Resources\\Boot\\dmg_rom.bin"));
            //info = new RomInfo(File.ReadAllBytes("Resources\\Boot\\marioland2.gb"));
            bus = new MemoryBus(info);

            cpu = new CPU(bus);
            video = new Video(bus, viewPanel.Handle);
            // cpu.Reset();

            cpu.PC = 0;

            hexViewControl.MemoryBus = bus;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            video.Clear();
            video.Present();
        }


        private void refreshRegistersButton_Click(object sender, EventArgs e)
        {
            afProcessorRegisterView.Value = cpu.GetRegister(Register.AF);
            bcProcessorRegisterView.Value = cpu.GetRegister(Register.BC);
            deProcessorRegisterView.Value = cpu.GetRegister(Register.DE);
            hlProcessorRegisterView.Value = cpu.GetRegister(Register.HL);
            spProcessorRegisterView.Value = cpu.GetRegister(Register.SP);
            pcProcessorRegisterView.Value = cpu.GetRegister(Register.PC);

            // interruptsEnabledCheckBox.Checked = cpu.InterruptsMasterEnabled;
        }

        private void pulseClockButton_Click(object sender, EventArgs e)
        {
            /*
            processor.PulseClock();

            afProcessorRegisterView.Value = processor.GetRegister(Register.AF);
            bcProcessorRegisterView.Value = processor.GetRegister(Register.BC);
            deProcessorRegisterView.Value = processor.GetRegister(Register.DE);
            hlProcessorRegisterView.Value = processor.GetRegister(Register.HL);
            spProcessorRegisterView.Value = processor.GetRegister(Register.SP);
            pcProcessorRegisterView.Value = processor.GetRegister(Register.PC);

            interruptsEnabledCheckBox.Checked = processor.InterruptsMasterEnabled;
            */
        }

        private void consumeInstructionButton_Click(object sender, EventArgs e)
        {
            cpu.Execute();

            //  Console.WriteLine($"Consumed instruction that had {cycle} cycles");
            video.Update(cpu.Cycles);

            updateProcessorInfo();
            
        }

        System.Timers.Timer? loopTimer = null;


        bool stopTimer = true;

        private void button4_Click(object sender, EventArgs e)
        {

            int maxCycles = 69905;


            stopTimer = false;


            loopTimer = new System.Timers.Timer();
            loopTimer.Interval = 1;
            loopTimer.Elapsed += LoopTimer_Elapsed;
            loopTimer.AutoReset = false;
            loopTimer.Enabled = true;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            stopTimer = true;
            updateProcessorInfo();
        }

        private void LoopTimer_Elapsed(object? sender, System.Timers.ElapsedEventArgs e)
        {
            // Stopwatch watch = new Stopwatch();

            int blah = 0;

            long elapsed = 0;

            Stopwatch watch = new();

            watch.Start();

            int cyclesPerSecond = 4190000;
            float frameRate = 59.72f;
            float speedMultiplier = 1f;
            float cyclesPerFrame = cyclesPerSecond / frameRate * speedMultiplier;
            float cyclesAccumulated = 0f;

            float secondsPerFrame = 1 / frameRate;

            while (!stopTimer)
            {
                while (cyclesAccumulated < cyclesPerFrame)
                {
                    cpu.Execute();
                    video.Update(cpu.Cycles);
                    cyclesAccumulated += cpu.Cycles;
                }

                if (watch.Elapsed.TotalSeconds > secondsPerFrame)
                {
                    watch.Restart();
                    rawPanel.Invalidate();
                    hexViewControl.Invoke(updateProcessorInfo);
                    cyclesAccumulated -= cyclesPerFrame;
                }
                else
                {
                    Thread.Yield();
                }
            }
        }

        private void rawPanel_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.Clear(Color.Black);

            if (video is null)
                return;

            using Bitmap bmp = new Bitmap(rawPanel.Width, rawPanel.Height);

            for (var y = 0; y < rawPanel.Height; y++)
            {
                for (var x = 0; x < rawPanel.Width; x++)
                {
                    // Console.WriteLine($"{(y * rawPanel.Width) + x} / 23,040" );

                    uint color = video.GetPixel((byte)x, (byte)y);

                    byte r = (byte)((color & 0xFF000000) >> 24);
                    byte g = (byte)((color & 0x00FF0000) >> 16);
                    byte b = (byte)((color & 0x0000FF00) >> 8);

                    bmp.SetPixel(x, y, Color.FromArgb(r, g, b));
                }
            }

            e.Graphics.DrawImage(bmp, 0, 0);
        }

        private void checkAddressButton_Click(object sender, EventArgs e)
        {
            addressLabel.Text = $"Value: 0x{(bus.Read((ushort)checkAddressNumericUpDown.Value)).ToString("X")}";
        }

        private void button5_Click(object sender, EventArgs e)
        {
            rawPanel.Invalidate();
        }


        private void button6_Click(object sender, EventArgs e)
        {

            // 16x24 = 384
            // where each tile is 8x8 pixels
            using Bitmap temp = new Bitmap(16 * 8, 32 * 8);
            ushort addr = 0x8000;

            byte[] pixelBuffer = new byte[8];

            byte[] tileData = new byte[16];

            for (var tileID = 0; tileID < 384; tileID++)
            {
                ReadTileData();

                RenderTileData(tileID);

                ClearTileData();
            }

            temp.Save("VRAM.png", System.Drawing.Imaging.ImageFormat.Png);

            return;

            void ReadTileData()
            {
                for (var i = 0; i < 16; i++)
                {
                    tileData[i] = bus.Read(addr++);
                }
            }

            void ClearTileData()
            {
                for (var i = 0; i < 16; i++)
                    tileData[i] = 0x00;

                for (var i = 0; i < 8; i++)
                    pixelBuffer[i] = 0x00;
            }

            void RenderTileData(int tileID)
            {
                // Iterate through each scanline
                for (var y = 0; y < 8; y++)
                {
                    byte lhs = tileData[(y * 2)];
                    byte rhs = tileData[(y * 2) + 1];

                    byte colorByte = 0;

                    // Iterate through each pixel
                    for (var x = 0; x < 8; x++)
                    {
                        var bit = 7 - x;

                        colorByte = (byte)((lhs & (0b1 << (7 - x))) != 0 ? 0b01 : 0b00);
                        colorByte |= (byte)((rhs & (0b1 << (7 - x))) != 0 ? 0b10 : 0b00);


                        Color c = Color.FromArgb(0x08, 0x18, 0x20);

                        switch (colorByte)
                        {
                            case 0:
                                c = Color.FromArgb(0x08, 0x18, 0x20);
                                break;
                            case 1:
                                c = Color.FromArgb(0x34, 0x68, 0x56);
                                break;
                            case 2:
                                c = Color.FromArgb(0x88, 0xC0, 0x70);
                                break;
                            case 3:
                                c = Color.FromArgb(0xE0, 0xF8, 0xD0);
                                break;
                        }

                        temp.SetPixel(((tileID % 16) * 8) + x, ((tileID / 16) * 8) + y, c);

                    }


                }





            }

        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            runUntilRegisterComboBox.SelectedIndex = 0;
            runUntilRegisterOperatorComboBox.SelectedIndex = 0;

        }

        private void runUntilRunButton_Click(object sender, EventArgs e)
        {
            runUntilRegisterComboBox.Enabled = false;
            runUntilRegisterOperatorComboBox.Enabled = false;
            runUntilRegisterValueNumericUpDown.Enabled = false;

            Register register = (Register)runUntilRegisterComboBox.SelectedIndex;
            ushort valueToMatch = (ushort)runUntilRegisterValueNumericUpDown.Value;
            int @operator = runUntilRegisterOperatorComboBox.SelectedIndex;

            Console.WriteLine($"Waiting for {cpu.GetRegister((Register)runUntilRegisterComboBox.SelectedIndex)} {runUntilRegisterOperatorComboBox.SelectedItem} {(ushort)runUntilRegisterValueNumericUpDown.Value}");

            while (true)
            {
                cpu.Execute();
                video.Update(cpu.Cycles);

                ushort value = cpu.GetRegister(register);

                Console.Write($"Running until: {string.Format($"{{0:X04}} {runUntilRegisterOperatorComboBox.SelectedItem} {{1:X04}}", value, valueToMatch)}\r");
                bool conditionMatched = @operator switch
                {
                    0 => value == valueToMatch, // ==
                    1 => value != valueToMatch, // !=
                    2 => value <= valueToMatch,// <=
                    3 => value >= valueToMatch,// >=
                    4 => value < valueToMatch,// <
                    5 => value > valueToMatch,// >
                    _ => false
                };

                if (conditionMatched)
                    break;
            }

            runUntilRegisterComboBox.Enabled = true;
            runUntilRegisterOperatorComboBox.Enabled = true;
            runUntilRegisterValueNumericUpDown.Enabled = true;


            updateProcessorInfo();
        }


        ushort highest = 0;

        private void updateProcessorInfo()
        {
            afProcessorRegisterView.Value = cpu.GetRegister(Register.AF);
            bcProcessorRegisterView.Value = cpu.GetRegister(Register.BC);
            deProcessorRegisterView.Value = cpu.GetRegister(Register.DE);
            hlProcessorRegisterView.Value = cpu.GetRegister(Register.HL);
            spProcessorRegisterView.Value = cpu.GetRegister(Register.SP);
            pcProcessorRegisterView.Value = cpu.GetRegister(Register.PC);

            hexViewControl.PCAddress = cpu.GetRegister(Register.PC);

            /*
            interruptsEnabledCheckBox.Checked = cpu.InterruptsMasterEnabled;
            
            processorFlagsLabel.Text = $"Flags: " +
                $"{(processor.GetFlag(Processor.Flags.Z) ? "Z" : "0")}" +
                $"{(processor.GetFlag(Processor.Flags.N) ? "N" : "0")}" +
                $"{(processor.GetFlag(Processor.Flags.H) ? "H" : "0")}" +
                $"{(processor.GetFlag(Processor.Flags.C) ? "C" : "0")}";

            hexViewControl.PCAddress = processor.GetRegister(Register.PC);

            if (highest < processor.PC)
            {
                label1.Text = $"Highest: 0x{processor.PC.ToString("X04")}";
                highest = processor.PC;
            }
            */

            return;
        }
    }
}