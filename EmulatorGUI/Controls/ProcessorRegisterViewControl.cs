using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace EmulatorGUI.EmulatorLib
{
    public partial class ProcessorRegisterViewControl : UserControl
    {
        public ProcessorRegisterViewControl()
        {
            InitializeComponent();
        }

        private void ProcessorRegisterViewControl_Load(object sender, EventArgs e)
        {

        }

        public string RegisterName
        {
            get => registerNameLabel.Text.Substring(0, 2);
            set => registerNameLabel.Text = $"{value}:";
        }

        public ushort Value
        {
            get => (ushort)registerValueNumericUpDown.Value;
            set => registerValueNumericUpDown.Value = value;
        }

        private void registerValueNumericUpDown_ValueChanged(object sender, EventArgs e)
        {

        }
    }
}
