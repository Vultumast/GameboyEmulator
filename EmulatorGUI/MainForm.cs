using EmulatorGUI.EmulatorLib;

namespace EmulatorGUI
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        MemoryBus bus = new();
        Processor? processor = null;
        Video? video = null;


        private void button1_Click(object sender, EventArgs e)
        {
            processor = new Processor(bus);
            video = new Video(bus, viewPanel.Handle);
            processor.Reset();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            video.Clear();
            video.Present();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            byte[] data = File.ReadAllBytes("rom.gb");

            RomInfo rom = new(data);

            //byte[] bank0Data = new byte[0x4000];

            //Array.Copy(data, bank0Data, bank0Data.Length);

            //var value = bus.Read(0);
            //bus.WriteROM(bank0Data);

            for (ushort i = 0; i < 0x8000; i++)
                bus.Write(i, data[i]);

            Console.WriteLine($"\"{rom.GameName}\"");
        }

        private void refreshRegistersButton_Click(object sender, EventArgs e)
        {
            registerAFNumericUpDown.Value = processor.GetRegister(Register.AF);
            registerBCNumericUpDown.Value = processor.GetRegister(Register.BC);
            registerDENumericUpDown.Value = processor.GetRegister(Register.DE);
            registerHLNumericUpDown.Value = processor.GetRegister(Register.HL);
            registerSPNumericUpDown.Value = processor.GetRegister(Register.SP);
            registerPCNumericUpDown.Value = processor.GetRegister(Register.PC);
        }

        private void pulseClockButton_Click(object sender, EventArgs e)
        {
            processor.PulseClock();

            registerANumericUpDown.Value = processor.GetRegister(Register.A);
            registerFNumericUpDown.Value = (processor.GetRegister(Register.AF) & 0x0F);

            registerAFNumericUpDown.Value = processor.GetRegister(Register.AF);
            registerBCNumericUpDown.Value = processor.GetRegister(Register.BC);
            registerDENumericUpDown.Value = processor.GetRegister(Register.DE);
            registerHLNumericUpDown.Value = processor.GetRegister(Register.HL);
            registerSPNumericUpDown.Value = processor.GetRegister(Register.SP);
            registerPCNumericUpDown.Value = processor.GetRegister(Register.PC);
        }

        System.Timers.Timer? loopTimer = null;

        private void button4_Click(object sender, EventArgs e)
        {
            loopTimer = new System.Timers.Timer();
            loopTimer.Interval = 16;
            loopTimer.Elapsed += LoopTimer_Elapsed;
            loopTimer.AutoReset = true;
            loopTimer.Enabled = true;
        }

        byte cyclesThisUpdate = 0;
        private void LoopTimer_Elapsed(object? sender, System.Timers.ElapsedEventArgs e)
        {

            int maxCycles = 69905;

            processor.PulseClock();
            this.Invoke(new MethodInvoker(delegate
            {
                registerANumericUpDown.Value = processor.GetRegister(Register.A);
                registerFNumericUpDown.Value = (processor.GetRegister(Register.AF) & 0x0F);

                registerAFNumericUpDown.Value = processor.GetRegister(Register.AF);
                registerBCNumericUpDown.Value = processor.GetRegister(Register.BC);
                registerDENumericUpDown.Value = processor.GetRegister(Register.DE);
                registerHLNumericUpDown.Value = processor.GetRegister(Register.HL);
                registerSPNumericUpDown.Value = processor.GetRegister(Register.SP);
                registerPCNumericUpDown.Value = processor.GetRegister(Register.PC);
            }));


            var remainingCycles = processor.RemainingCycles;

            if (remainingCycles == 0)
            {
                // Console.WriteLine($"updating video cycles: {cyclesThisUpdate}");
                video.Update(cyclesThisUpdate);

                cyclesThisUpdate = 0;
            }
            else
                cyclesThisUpdate++;
            rawPanel.Invalidate();
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

        }
    }
}
