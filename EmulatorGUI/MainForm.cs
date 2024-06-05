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
    }
}
