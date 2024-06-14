namespace EmulatorGUI
{
    partial class MainForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            viewPanel = new Panel();
            button1 = new Button();
            button2 = new Button();
            refreshRegistersButton = new Button();
            pulseClockButton = new Button();
            button4 = new Button();
            rawPanel = new Panel();
            checkAddressNumericUpDown = new NumericUpDown();
            checkAddressButton = new Button();
            addressLabel = new Label();
            button5 = new Button();
            hexViewControl = new Controls.HexViewControl();
            afProcessorRegisterView = new EmulatorLib.ProcessorRegisterViewControl();
            bcProcessorRegisterView = new EmulatorLib.ProcessorRegisterViewControl();
            deProcessorRegisterView = new EmulatorLib.ProcessorRegisterViewControl();
            hlProcessorRegisterView = new EmulatorLib.ProcessorRegisterViewControl();
            spProcessorRegisterView = new EmulatorLib.ProcessorRegisterViewControl();
            pcProcessorRegisterView = new EmulatorLib.ProcessorRegisterViewControl();
            interruptsEnabledCheckBox = new CheckBox();
            consumeInstructionButton = new Button();
            groupBox1 = new GroupBox();
            runUntilRegisterValueNumericUpDown = new NumericUpDown();
            runUntilRegisterOperatorComboBox = new ComboBox();
            runUntilRegisterComboBox = new ComboBox();
            runUntilRunButton = new Button();
            ((System.ComponentModel.ISupportInitialize)checkAddressNumericUpDown).BeginInit();
            groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)runUntilRegisterValueNumericUpDown).BeginInit();
            SuspendLayout();
            // 
            // viewPanel
            // 
            viewPanel.Location = new Point(40, 34);
            viewPanel.Name = "viewPanel";
            viewPanel.Size = new Size(310, 222);
            viewPanel.TabIndex = 0;
            // 
            // button1
            // 
            button1.Location = new Point(356, 34);
            button1.Name = "button1";
            button1.Size = new Size(121, 23);
            button1.TabIndex = 1;
            button1.Text = "create render";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // button2
            // 
            button2.Location = new Point(356, 63);
            button2.Name = "button2";
            button2.Size = new Size(121, 23);
            button2.TabIndex = 2;
            button2.Text = "clear -> present";
            button2.UseVisualStyleBackColor = true;
            button2.Click += button2_Click;
            // 
            // refreshRegistersButton
            // 
            refreshRegistersButton.Location = new Point(765, 61);
            refreshRegistersButton.Name = "refreshRegistersButton";
            refreshRegistersButton.Size = new Size(149, 23);
            refreshRegistersButton.TabIndex = 16;
            refreshRegistersButton.Text = "refresh reg";
            refreshRegistersButton.UseVisualStyleBackColor = true;
            refreshRegistersButton.Click += refreshRegistersButton_Click;
            // 
            // pulseClockButton
            // 
            pulseClockButton.Location = new Point(411, 159);
            pulseClockButton.Name = "pulseClockButton";
            pulseClockButton.Size = new Size(149, 23);
            pulseClockButton.TabIndex = 17;
            pulseClockButton.Text = "pulse clock";
            pulseClockButton.UseVisualStyleBackColor = true;
            pulseClockButton.Click += pulseClockButton_Click;
            // 
            // button4
            // 
            button4.Location = new Point(411, 412);
            button4.Name = "button4";
            button4.Size = new Size(149, 23);
            button4.TabIndex = 20;
            button4.Text = "start";
            button4.UseVisualStyleBackColor = true;
            button4.Click += button4_Click;
            // 
            // rawPanel
            // 
            rawPanel.Location = new Point(40, 262);
            rawPanel.Name = "rawPanel";
            rawPanel.Size = new Size(160, 144);
            rawPanel.TabIndex = 21;
            rawPanel.Paint += rawPanel_Paint;
            // 
            // checkAddressNumericUpDown
            // 
            checkAddressNumericUpDown.Hexadecimal = true;
            checkAddressNumericUpDown.Location = new Point(533, 63);
            checkAddressNumericUpDown.Maximum = new decimal(new int[] { 65535, 0, 0, 0 });
            checkAddressNumericUpDown.Name = "checkAddressNumericUpDown";
            checkAddressNumericUpDown.Size = new Size(120, 23);
            checkAddressNumericUpDown.TabIndex = 22;
            // 
            // checkAddressButton
            // 
            checkAddressButton.Location = new Point(659, 63);
            checkAddressButton.Name = "checkAddressButton";
            checkAddressButton.Size = new Size(66, 23);
            checkAddressButton.TabIndex = 23;
            checkAddressButton.Text = "check";
            checkAddressButton.UseVisualStyleBackColor = true;
            checkAddressButton.Click += checkAddressButton_Click;
            // 
            // addressLabel
            // 
            addressLabel.AutoSize = true;
            addressLabel.Location = new Point(533, 89);
            addressLabel.Name = "addressLabel";
            addressLabel.Size = new Size(65, 15);
            addressLabel.TabIndex = 24;
            addressLabel.Text = "Value: 0x00";
            // 
            // button5
            // 
            button5.Location = new Point(206, 262);
            button5.Name = "button5";
            button5.Size = new Size(102, 23);
            button5.TabIndex = 25;
            button5.Text = "invalidate panel";
            button5.UseVisualStyleBackColor = true;
            button5.Click += button5_Click;
            // 
            // hexViewControl
            // 
            hexViewControl.Font = new Font("Consolas", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            hexViewControl.HotTrackPosition = new Point(0, 0);
            hexViewControl.Location = new Point(566, 121);
            hexViewControl.MemoryBus = null;
            hexViewControl.Name = "hexViewControl";
            hexViewControl.Size = new Size(540, 451);
            hexViewControl.TabIndex = 26;
            // 
            // afProcessorRegisterView
            // 
            afProcessorRegisterView.Location = new Point(411, 188);
            afProcessorRegisterView.Name = "afProcessorRegisterView";
            afProcessorRegisterView.RegisterName = "AF";
            afProcessorRegisterView.Size = new Size(149, 22);
            afProcessorRegisterView.TabIndex = 27;
            afProcessorRegisterView.Value = (ushort)0;
            // 
            // bcProcessorRegisterView
            // 
            bcProcessorRegisterView.Location = new Point(411, 216);
            bcProcessorRegisterView.Name = "bcProcessorRegisterView";
            bcProcessorRegisterView.RegisterName = "BC";
            bcProcessorRegisterView.Size = new Size(149, 22);
            bcProcessorRegisterView.TabIndex = 28;
            bcProcessorRegisterView.Value = (ushort)0;
            // 
            // deProcessorRegisterView
            // 
            deProcessorRegisterView.Location = new Point(411, 244);
            deProcessorRegisterView.Name = "deProcessorRegisterView";
            deProcessorRegisterView.RegisterName = "DE";
            deProcessorRegisterView.Size = new Size(149, 22);
            deProcessorRegisterView.TabIndex = 29;
            deProcessorRegisterView.Value = (ushort)0;
            // 
            // hlProcessorRegisterView
            // 
            hlProcessorRegisterView.Location = new Point(411, 272);
            hlProcessorRegisterView.Name = "hlProcessorRegisterView";
            hlProcessorRegisterView.RegisterName = "HL";
            hlProcessorRegisterView.Size = new Size(149, 22);
            hlProcessorRegisterView.TabIndex = 30;
            hlProcessorRegisterView.Value = (ushort)0;
            // 
            // spProcessorRegisterView
            // 
            spProcessorRegisterView.Location = new Point(411, 300);
            spProcessorRegisterView.Name = "spProcessorRegisterView";
            spProcessorRegisterView.RegisterName = "SP";
            spProcessorRegisterView.Size = new Size(149, 22);
            spProcessorRegisterView.TabIndex = 31;
            spProcessorRegisterView.Value = (ushort)0;
            // 
            // pcProcessorRegisterView
            // 
            pcProcessorRegisterView.Location = new Point(411, 328);
            pcProcessorRegisterView.Name = "pcProcessorRegisterView";
            pcProcessorRegisterView.RegisterName = "PC";
            pcProcessorRegisterView.Size = new Size(149, 22);
            pcProcessorRegisterView.TabIndex = 32;
            pcProcessorRegisterView.Value = (ushort)0;
            // 
            // interruptsEnabledCheckBox
            // 
            interruptsEnabledCheckBox.AutoSize = true;
            interruptsEnabledCheckBox.Location = new Point(411, 356);
            interruptsEnabledCheckBox.Name = "interruptsEnabledCheckBox";
            interruptsEnabledCheckBox.Size = new Size(122, 19);
            interruptsEnabledCheckBox.TabIndex = 33;
            interruptsEnabledCheckBox.Text = "Interrupts Enabled";
            interruptsEnabledCheckBox.UseVisualStyleBackColor = true;
            // 
            // consumeInstructionButton
            // 
            consumeInstructionButton.Location = new Point(411, 130);
            consumeInstructionButton.Name = "consumeInstructionButton";
            consumeInstructionButton.Size = new Size(149, 23);
            consumeInstructionButton.TabIndex = 34;
            consumeInstructionButton.Text = "consume instruction";
            consumeInstructionButton.UseVisualStyleBackColor = true;
            consumeInstructionButton.Click += consumeInstructionButton_Click;
            // 
            // groupBox1
            // 
            groupBox1.Controls.Add(runUntilRegisterValueNumericUpDown);
            groupBox1.Controls.Add(runUntilRegisterOperatorComboBox);
            groupBox1.Controls.Add(runUntilRegisterComboBox);
            groupBox1.Controls.Add(runUntilRunButton);
            groupBox1.Location = new Point(40, 412);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(329, 100);
            groupBox1.TabIndex = 35;
            groupBox1.TabStop = false;
            groupBox1.Text = "Run Until";
            // 
            // runUntilRegisterValueNumericUpDown
            // 
            runUntilRegisterValueNumericUpDown.Hexadecimal = true;
            runUntilRegisterValueNumericUpDown.Location = new Point(215, 22);
            runUntilRegisterValueNumericUpDown.Maximum = new decimal(new int[] { 65535, 0, 0, 0 });
            runUntilRegisterValueNumericUpDown.Name = "runUntilRegisterValueNumericUpDown";
            runUntilRegisterValueNumericUpDown.Size = new Size(108, 23);
            runUntilRegisterValueNumericUpDown.TabIndex = 36;
            // 
            // runUntilRegisterOperatorComboBox
            // 
            runUntilRegisterOperatorComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            runUntilRegisterOperatorComboBox.FormattingEnabled = true;
            runUntilRegisterOperatorComboBox.Items.AddRange(new object[] { "==", "!=", "<=", ">=", ">", "<" });
            runUntilRegisterOperatorComboBox.Location = new Point(133, 22);
            runUntilRegisterOperatorComboBox.Name = "runUntilRegisterOperatorComboBox";
            runUntilRegisterOperatorComboBox.Size = new Size(76, 23);
            runUntilRegisterOperatorComboBox.TabIndex = 37;
            // 
            // runUntilRegisterComboBox
            // 
            runUntilRegisterComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            runUntilRegisterComboBox.FormattingEnabled = true;
            runUntilRegisterComboBox.Items.AddRange(new object[] { "A", "B", "C", "D", "E", "H", "L", "AF", "BC", "DE", "HL", "SP", "PC" });
            runUntilRegisterComboBox.Location = new Point(6, 22);
            runUntilRegisterComboBox.Name = "runUntilRegisterComboBox";
            runUntilRegisterComboBox.Size = new Size(121, 23);
            runUntilRegisterComboBox.TabIndex = 36;
            // 
            // runUntilRunButton
            // 
            runUntilRunButton.Location = new Point(6, 51);
            runUntilRunButton.Name = "runUntilRunButton";
            runUntilRunButton.Size = new Size(149, 23);
            runUntilRunButton.TabIndex = 36;
            runUntilRunButton.Text = "Run";
            runUntilRunButton.UseVisualStyleBackColor = true;
            runUntilRunButton.Click += runUntilRunButton_Click;
            // 
            // MainForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1118, 584);
            Controls.Add(groupBox1);
            Controls.Add(consumeInstructionButton);
            Controls.Add(interruptsEnabledCheckBox);
            Controls.Add(pcProcessorRegisterView);
            Controls.Add(spProcessorRegisterView);
            Controls.Add(hlProcessorRegisterView);
            Controls.Add(deProcessorRegisterView);
            Controls.Add(bcProcessorRegisterView);
            Controls.Add(afProcessorRegisterView);
            Controls.Add(hexViewControl);
            Controls.Add(button5);
            Controls.Add(addressLabel);
            Controls.Add(checkAddressButton);
            Controls.Add(checkAddressNumericUpDown);
            Controls.Add(rawPanel);
            Controls.Add(button4);
            Controls.Add(pulseClockButton);
            Controls.Add(refreshRegistersButton);
            Controls.Add(button2);
            Controls.Add(button1);
            Controls.Add(viewPanel);
            DoubleBuffered = true;
            Name = "MainForm";
            Text = "Form1";
            Load += MainForm_Load;
            ((System.ComponentModel.ISupportInitialize)checkAddressNumericUpDown).EndInit();
            groupBox1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)runUntilRegisterValueNumericUpDown).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Panel viewPanel;
        private Button button1;
        private Button button2;
        private Button refreshRegistersButton;
        private Button pulseClockButton;
        private Button button4;
        private Panel rawPanel;
        private NumericUpDown checkAddressNumericUpDown;
        private Button checkAddressButton;
        private Label addressLabel;
        private Button button5;
        private Controls.HexViewControl hexViewControl;
        private EmulatorLib.ProcessorRegisterViewControl afProcessorRegisterView;
        private EmulatorLib.ProcessorRegisterViewControl bcProcessorRegisterView;
        private EmulatorLib.ProcessorRegisterViewControl deProcessorRegisterView;
        private EmulatorLib.ProcessorRegisterViewControl hlProcessorRegisterView;
        private EmulatorLib.ProcessorRegisterViewControl spProcessorRegisterView;
        private EmulatorLib.ProcessorRegisterViewControl pcProcessorRegisterView;
        private CheckBox interruptsEnabledCheckBox;
        private Button consumeInstructionButton;
        private GroupBox groupBox1;
        private Button runUntilRunButton;
        private ComboBox runUntilRegisterComboBox;
        private ComboBox runUntilRegisterOperatorComboBox;
        private NumericUpDown runUntilRegisterValueNumericUpDown;
    }
}
