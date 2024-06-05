using EmulatorGUI.EmulatorLib;

namespace EmulatorGUI
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        MemoryBus bus = new MemoryBus();
        Video? video = null;


        private void button1_Click(object sender, EventArgs e)
        {
            video = new Video(bus, viewPanel.Handle);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            video.Clear();
            video.Present();
        }
    }
}
