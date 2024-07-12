using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace EmulatorGUI.Forms
{
    public partial class ConfigureForm : Form
    {
        public ConfigureForm()
        {
            InitializeComponent();
        }

        private void ConfigureForm_Load(object sender, EventArgs e)
        {
            if (!Directory.Exists("boot"))
                Directory.CreateDirectory("boot");

            dmgBootROMComboBox.Items.Add("None");
            gbcBootROMComboBox.Items.Add("None");

            var files = Directory.GetFiles("boot", "*.*", SearchOption.AllDirectories);

            foreach ( var file in files) 
            {
                var path = file.Substring(file.IndexOf("boot") + "boot".Length + 1);
                dmgBootROMComboBox.Items.Add(path);
                gbcBootROMComboBox.Items.Add(path);
            }
            
        }
    }
}
