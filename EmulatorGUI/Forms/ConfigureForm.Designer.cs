namespace EmulatorGUI.Forms
{
    partial class ConfigureForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            dmgBootROMComboBox = new ComboBox();
            gbcBootROMComboBox = new ComboBox();
            tabControl1 = new TabControl();
            gameboyTabPage = new TabPage();
            groupBox1 = new GroupBox();
            groupBox2 = new GroupBox();
            gbRandomizeRAMCheckBox = new CheckBox();
            label1 = new Label();
            gameboyColorTabPage = new TabPage();
            label2 = new Label();
            commonToolTip = new ToolTip(components);
            echoramConfigurationControl1 = new Controls.EchoRAMConfigurationControl();
            tabControl1.SuspendLayout();
            gameboyTabPage.SuspendLayout();
            groupBox1.SuspendLayout();
            gameboyColorTabPage.SuspendLayout();
            SuspendLayout();
            // 
            // dmgBootROMComboBox
            // 
            dmgBootROMComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            dmgBootROMComboBox.FormattingEnabled = true;
            dmgBootROMComboBox.Location = new Point(77, 16);
            dmgBootROMComboBox.Name = "dmgBootROMComboBox";
            dmgBootROMComboBox.Size = new Size(121, 23);
            dmgBootROMComboBox.TabIndex = 0;
            // 
            // gbcBootROMComboBox
            // 
            gbcBootROMComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            gbcBootROMComboBox.FormattingEnabled = true;
            gbcBootROMComboBox.Location = new Point(79, 6);
            gbcBootROMComboBox.Name = "gbcBootROMComboBox";
            gbcBootROMComboBox.Size = new Size(121, 23);
            gbcBootROMComboBox.TabIndex = 1;
            // 
            // tabControl1
            // 
            tabControl1.Controls.Add(gameboyTabPage);
            tabControl1.Controls.Add(gameboyColorTabPage);
            tabControl1.Location = new Point(0, 0);
            tabControl1.Name = "tabControl1";
            tabControl1.SelectedIndex = 0;
            tabControl1.Size = new Size(623, 426);
            tabControl1.TabIndex = 2;
            // 
            // gameboyTabPage
            // 
            gameboyTabPage.BackColor = SystemColors.Control;
            gameboyTabPage.Controls.Add(echoramConfigurationControl1);
            gameboyTabPage.Controls.Add(groupBox1);
            gameboyTabPage.Location = new Point(4, 24);
            gameboyTabPage.Name = "gameboyTabPage";
            gameboyTabPage.Padding = new Padding(3);
            gameboyTabPage.Size = new Size(615, 398);
            gameboyTabPage.TabIndex = 1;
            gameboyTabPage.Text = "Gameboy";
            // 
            // groupBox1
            // 
            groupBox1.Controls.Add(groupBox2);
            groupBox1.Controls.Add(gbRandomizeRAMCheckBox);
            groupBox1.Controls.Add(label1);
            groupBox1.Controls.Add(dmgBootROMComboBox);
            groupBox1.Location = new Point(8, 6);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(492, 162);
            groupBox1.TabIndex = 3;
            groupBox1.TabStop = false;
            groupBox1.Text = "Startup";
            // 
            // groupBox2
            // 
            groupBox2.Location = new Point(6, 45);
            groupBox2.Name = "groupBox2";
            groupBox2.Size = new Size(480, 111);
            groupBox2.TabIndex = 4;
            groupBox2.TabStop = false;
            groupBox2.Text = "Initial Register Values";
            // 
            // gbRandomizeRAMCheckBox
            // 
            gbRandomizeRAMCheckBox.AutoSize = true;
            gbRandomizeRAMCheckBox.Location = new Point(204, 18);
            gbRandomizeRAMCheckBox.Name = "gbRandomizeRAMCheckBox";
            gbRandomizeRAMCheckBox.Size = new Size(114, 19);
            gbRandomizeRAMCheckBox.TabIndex = 3;
            gbRandomizeRAMCheckBox.Text = "Randomize RAM";
            commonToolTip.SetToolTip(gbRandomizeRAMCheckBox, "Randomize the contents of RAM on startup");
            gbRandomizeRAMCheckBox.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(6, 19);
            label1.Name = "label1";
            label1.Size = new Size(65, 15);
            label1.TabIndex = 3;
            label1.Text = "Boot ROM:";
            // 
            // gameboyColorTabPage
            // 
            gameboyColorTabPage.BackColor = SystemColors.Control;
            gameboyColorTabPage.Controls.Add(label2);
            gameboyColorTabPage.Controls.Add(gbcBootROMComboBox);
            gameboyColorTabPage.Location = new Point(4, 24);
            gameboyColorTabPage.Name = "gameboyColorTabPage";
            gameboyColorTabPage.Padding = new Padding(3);
            gameboyColorTabPage.Size = new Size(615, 398);
            gameboyColorTabPage.TabIndex = 2;
            gameboyColorTabPage.Text = "Gameboy Color";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(8, 9);
            label2.Name = "label2";
            label2.Size = new Size(65, 15);
            label2.TabIndex = 5;
            label2.Text = "Boot ROM:";
            // 
            // echoramConfigurationControl1
            // 
            echoramConfigurationControl1.Location = new Point(8, 174);
            echoramConfigurationControl1.Name = "echoramConfigurationControl1";
            echoramConfigurationControl1.Size = new Size(189, 142);
            echoramConfigurationControl1.TabIndex = 4;
            // 
            // ConfigureForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = SystemColors.ButtonHighlight;
            ClientSize = new Size(800, 450);
            Controls.Add(tabControl1);
            Name = "ConfigureForm";
            Text = "ConfigureForm";
            Load += ConfigureForm_Load;
            tabControl1.ResumeLayout(false);
            gameboyTabPage.ResumeLayout(false);
            groupBox1.ResumeLayout(false);
            groupBox1.PerformLayout();
            gameboyColorTabPage.ResumeLayout(false);
            gameboyColorTabPage.PerformLayout();
            ResumeLayout(false);
        }

        #endregion

        private ComboBox dmgBootROMComboBox;
        private ComboBox gbcBootROMComboBox;
        private TabControl tabControl1;
        private TabPage gameboyTabPage;
        private Label label1;
        private TabPage gameboyColorTabPage;
        private Label label2;
        private GroupBox groupBox1;
        private GroupBox groupBox2;
        private CheckBox gbRandomizeRAMCheckBox;
        private ToolTip commonToolTip;
        private Controls.EchoRAMConfigurationControl echoramConfigurationControl1;
    }
}