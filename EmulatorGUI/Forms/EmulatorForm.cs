using EmulatorGUI.EmulatorLib;
using EmulatorGUI.Forms;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace EmulatorGUI
{
    public partial class EmulatorForm : Form
    {
        public EmulatorForm()
        {
            InitializeComponent();
        }

        private void EmulatorForm_Load(object sender, EventArgs e)
        {
            if (!Directory.Exists("boot"))
                Directory.CreateDirectory("boot");

        }

        RomInfo? _romInfo = null;

        #region Menustrip
        private void openRomToolStripMenuItem_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog dlg = new OpenFileDialog())
            {
                dlg.Title = "Select Gameboy or Gameboy Color ROM";
                if (dlg.ShowDialog() == DialogResult.OK)
                {
                    _romInfo?.Dispose();
                    _romInfo = null;

                    _romInfo = new RomInfo(File.ReadAllBytes(dlg.FileName));
                }
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        #region Emulation
        private void resetToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void shutdownToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void configureToolStripMenuItem_Click(object sender, EventArgs e)
        {
            using (ConfigureForm form = new ConfigureForm())
            {
                if (form.ShowDialog() == DialogResult.OK)
                {

                }
            }
        }

        private void insertGameCartridgeToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void insertLinkCableToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void removeGameCartridgeToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void removeLinkCableToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void resumeToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void pauseToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void nextFrameToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void nextCycleToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }
        #endregion
        #endregion
    }
}
