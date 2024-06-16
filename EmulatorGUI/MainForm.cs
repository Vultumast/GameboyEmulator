using EmulatorGUI.EmulatorLib;
using System.Diagnostics;
using System.Reflection.Metadata.Ecma335;

namespace EmulatorGUI
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }
        RomInfo? info = null;

        MemoryBus? bus = null;
        Processor? processor = null;
        Video? video = null;


        private void button1_Click(object sender, EventArgs e)
        {
            info = new RomInfo(File.ReadAllBytes("rom.gb"));


            bus = new MemoryBus(info);

            processor = new Processor(bus);
            video = new Video(bus, viewPanel.Handle);
            processor.Reset();

            hexViewControl.MemoryBus = bus;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            video.Clear();
            video.Present();
        }


        private void refreshRegistersButton_Click(object sender, EventArgs e)
        {
            afProcessorRegisterView.Value = processor.GetRegister(Register.AF);
            bcProcessorRegisterView.Value = processor.GetRegister(Register.BC);
            deProcessorRegisterView.Value = processor.GetRegister(Register.DE);
            hlProcessorRegisterView.Value = processor.GetRegister(Register.HL);
            spProcessorRegisterView.Value = processor.GetRegister(Register.SP);
            pcProcessorRegisterView.Value = processor.GetRegister(Register.PC);

            interruptsEnabledCheckBox.Checked = processor.InterruptsMasterEnabled;
        }

        private void pulseClockButton_Click(object sender, EventArgs e)
        {
            processor.PulseClock();

            afProcessorRegisterView.Value = processor.GetRegister(Register.AF);
            bcProcessorRegisterView.Value = processor.GetRegister(Register.BC);
            deProcessorRegisterView.Value = processor.GetRegister(Register.DE);
            hlProcessorRegisterView.Value = processor.GetRegister(Register.HL);
            spProcessorRegisterView.Value = processor.GetRegister(Register.SP);
            pcProcessorRegisterView.Value = processor.GetRegister(Register.PC);

            interruptsEnabledCheckBox.Checked = processor.InterruptsMasterEnabled;
        }

        private void consumeInstructionButton_Click(object sender, EventArgs e)
        {
            var cycle = processor.RemainingCycles;
            processor.ConsumeInstruction();

            //  Console.WriteLine($"Consumed instruction that had {cycle} cycles");
            video.Update(cycle);

            updateProcessorInfo();
        }

        System.Timers.Timer? loopTimer = null;


        bool stopTimer = false;

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
            Stopwatch watch = new Stopwatch();

            int blah = 0;

            long elapsed = 0;

            while (true)
            {
                watch.Restart();

                var cycle = processor.RemainingCycles;
                processor.ConsumeInstruction();
                video.Update(cycle);
                // rawPanel.Invalidate();
                /*
                this.Invoke(new MethodInvoker(delegate
                {
                    afProcessorRegisterView.Value = processor.GetRegister(Register.AF);
                    bcProcessorRegisterView.Value = processor.GetRegister(Register.BC);
                    deProcessorRegisterView.Value = processor.GetRegister(Register.DE);
                    hlProcessorRegisterView.Value = processor.GetRegister(Register.HL);
                    spProcessorRegisterView.Value = processor.GetRegister(Register.SP);
                    pcProcessorRegisterView.Value = processor.GetRegister(Register.PC);

                    interruptsEnabledCheckBox.Checked = processor.InterruptsMasterEnabled;
                }));
                */

                Console.WriteLine(string.Format("PC: {0:X04}\r", processor.GetRegister(Register.PC)));
                // Console.WriteLine($"ELAPSED: {(float)elapsed / (float)Stopwatch.Frequency}");
                watch.Stop();
                elapsed = watch.ElapsedTicks;
                //Application.DoEvents();
                //Thread.Yield();

                if (stopTimer)
                    break;
            }
        }

        private void rawPanel_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.Clear(Color.Black);

            if (video is null)
                return;

            using Bitmap bmp = new Bitmap(rawPanel.Width, rawPanel.Height);

            for (var x = 0; x < rawPanel.Width; x++)
            {
                for (var y = 0; y < rawPanel.Height; y++)
                {
                    uint color = video.GetPixel((byte)x, (byte)y);

                    bmp.SetPixel(x, y, Color.FromArgb((byte)(color & 0xFF000000 >> 24), (byte)(color & 0x00FF0000 >> 16), (byte)(color & 0x0000FF00 >> 8)));
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

            Console.WriteLine($"Waiting for {processor.GetRegister((Register)runUntilRegisterComboBox.SelectedIndex)} {runUntilRegisterOperatorComboBox.SelectedItem} {(ushort)runUntilRegisterValueNumericUpDown.Value}");
            while (!getCondition())
            {
                var cycle = processor.RemainingCycles;
                processor.ConsumeInstruction();

                //  Console.WriteLine($"Consumed instruction that had {cycle} cycles");
                video.Update(cycle);
            }
            Console.WriteLine($"Done waiting!");

            runUntilRegisterComboBox.Enabled = true;
            runUntilRegisterOperatorComboBox.Enabled = true;
            runUntilRegisterValueNumericUpDown.Enabled = true;

            updateProcessorInfo();
            return;

            bool getCondition()
            {
                ushort value = processor.GetRegister((Register)runUntilRegisterComboBox.SelectedIndex);
                ushort valueToMatch = (ushort)runUntilRegisterValueNumericUpDown.Value;

                // Console.Write($"Running until: {string.Format($"{{0:X04}} {runUntilRegisterOperatorComboBox.SelectedItem} {{1:X04}}", value, valueToMatch)}\r");
                return runUntilRegisterOperatorComboBox.SelectedIndex switch
                {
                    0 => value == valueToMatch, // ==
                    1 => value != valueToMatch, // !=
                    2 => value <= valueToMatch,// <=
                    3 => value >= valueToMatch,// >=
                    4 => value < valueToMatch,// <
                    5 => value > valueToMatch,// >
                    _ => false
                };
            }
        }


        private void updateProcessorInfo()
        {
            afProcessorRegisterView.Value = processor.GetRegister(Register.AF);
            bcProcessorRegisterView.Value = processor.GetRegister(Register.BC);
            deProcessorRegisterView.Value = processor.GetRegister(Register.DE);
            hlProcessorRegisterView.Value = processor.GetRegister(Register.HL);
            spProcessorRegisterView.Value = processor.GetRegister(Register.SP);
            pcProcessorRegisterView.Value = processor.GetRegister(Register.PC);

            interruptsEnabledCheckBox.Checked = processor.InterruptsMasterEnabled;

            processorFlagsLabel.Text = $"Flags: " +
                $"{(processor.GetFlag(Processor.Flags.Z) ? "Z" : "0")}" +
                $"{(processor.GetFlag(Processor.Flags.N) ? "N" : "0")}" +
                $"{(processor.GetFlag(Processor.Flags.H) ? "H" : "0")}" +
                $"{(processor.GetFlag(Processor.Flags.C) ? "C" : "0")}";

            hexViewControl.PCAddress = processor.GetRegister(Register.PC);
        }

    }
}