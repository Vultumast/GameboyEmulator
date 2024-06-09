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
            registerAFNumericUpDown = new NumericUpDown();
            registerBCNumericUpDown = new NumericUpDown();
            registerDENumericUpDown = new NumericUpDown();
            registerHLNumericUpDown = new NumericUpDown();
            registerSPNumericUpDown = new NumericUpDown();
            registerPCNumericUpDown = new NumericUpDown();
            label1 = new Label();
            label2 = new Label();
            label3 = new Label();
            label4 = new Label();
            label5 = new Label();
            label6 = new Label();
            refreshRegistersButton = new Button();
            pulseClockButton = new Button();
            registerANumericUpDown = new NumericUpDown();
            registerFNumericUpDown = new NumericUpDown();
            button4 = new Button();
            rawPanel = new Panel();
            checkAddressNumericUpDown = new NumericUpDown();
            checkAddressButton = new Button();
            addressLabel = new Label();
            button5 = new Button();
            ((System.ComponentModel.ISupportInitialize)registerAFNumericUpDown).BeginInit();
            ((System.ComponentModel.ISupportInitialize)registerBCNumericUpDown).BeginInit();
            ((System.ComponentModel.ISupportInitialize)registerDENumericUpDown).BeginInit();
            ((System.ComponentModel.ISupportInitialize)registerHLNumericUpDown).BeginInit();
            ((System.ComponentModel.ISupportInitialize)registerSPNumericUpDown).BeginInit();
            ((System.ComponentModel.ISupportInitialize)registerPCNumericUpDown).BeginInit();
            ((System.ComponentModel.ISupportInitialize)registerANumericUpDown).BeginInit();
            ((System.ComponentModel.ISupportInitialize)registerFNumericUpDown).BeginInit();
            ((System.ComponentModel.ISupportInitialize)checkAddressNumericUpDown).BeginInit();
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
            // registerAFNumericUpDown
            // 
            registerAFNumericUpDown.Hexadecimal = true;
            registerAFNumericUpDown.Location = new Point(440, 188);
            registerAFNumericUpDown.Maximum = new decimal(new int[] { 65535, 0, 0, 0 });
            registerAFNumericUpDown.Name = "registerAFNumericUpDown";
            registerAFNumericUpDown.Size = new Size(120, 23);
            registerAFNumericUpDown.TabIndex = 4;
            // 
            // registerBCNumericUpDown
            // 
            registerBCNumericUpDown.Hexadecimal = true;
            registerBCNumericUpDown.Location = new Point(440, 217);
            registerBCNumericUpDown.Maximum = new decimal(new int[] { 65535, 0, 0, 0 });
            registerBCNumericUpDown.Name = "registerBCNumericUpDown";
            registerBCNumericUpDown.Size = new Size(120, 23);
            registerBCNumericUpDown.TabIndex = 5;
            // 
            // registerDENumericUpDown
            // 
            registerDENumericUpDown.Hexadecimal = true;
            registerDENumericUpDown.Location = new Point(440, 246);
            registerDENumericUpDown.Maximum = new decimal(new int[] { 65535, 0, 0, 0 });
            registerDENumericUpDown.Name = "registerDENumericUpDown";
            registerDENumericUpDown.Size = new Size(120, 23);
            registerDENumericUpDown.TabIndex = 6;
            // 
            // registerHLNumericUpDown
            // 
            registerHLNumericUpDown.Hexadecimal = true;
            registerHLNumericUpDown.Location = new Point(440, 275);
            registerHLNumericUpDown.Maximum = new decimal(new int[] { 65535, 0, 0, 0 });
            registerHLNumericUpDown.Name = "registerHLNumericUpDown";
            registerHLNumericUpDown.Size = new Size(120, 23);
            registerHLNumericUpDown.TabIndex = 7;
            // 
            // registerSPNumericUpDown
            // 
            registerSPNumericUpDown.Hexadecimal = true;
            registerSPNumericUpDown.Location = new Point(440, 304);
            registerSPNumericUpDown.Maximum = new decimal(new int[] { 65535, 0, 0, 0 });
            registerSPNumericUpDown.Name = "registerSPNumericUpDown";
            registerSPNumericUpDown.Size = new Size(120, 23);
            registerSPNumericUpDown.TabIndex = 8;
            // 
            // registerPCNumericUpDown
            // 
            registerPCNumericUpDown.Hexadecimal = true;
            registerPCNumericUpDown.Location = new Point(440, 333);
            registerPCNumericUpDown.Maximum = new decimal(new int[] { 65535, 0, 0, 0 });
            registerPCNumericUpDown.Name = "registerPCNumericUpDown";
            registerPCNumericUpDown.Size = new Size(120, 23);
            registerPCNumericUpDown.TabIndex = 9;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(410, 190);
            label1.Name = "label1";
            label1.Size = new Size(24, 15);
            label1.TabIndex = 10;
            label1.Text = "AF:";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(409, 335);
            label2.Name = "label2";
            label2.Size = new Size(25, 15);
            label2.TabIndex = 11;
            label2.Text = "PC:";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(411, 306);
            label3.Name = "label3";
            label3.Size = new Size(23, 15);
            label3.TabIndex = 12;
            label3.Text = "SP:";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(409, 277);
            label4.Name = "label4";
            label4.Size = new Size(25, 15);
            label4.TabIndex = 13;
            label4.Text = "HL:";
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new Point(410, 248);
            label5.Name = "label5";
            label5.Size = new Size(24, 15);
            label5.TabIndex = 14;
            label5.Text = "DE:";
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Location = new Point(409, 219);
            label6.Name = "label6";
            label6.Size = new Size(25, 15);
            label6.TabIndex = 15;
            label6.Text = "BC:";
            // 
            // refreshRegistersButton
            // 
            refreshRegistersButton.Location = new Point(411, 362);
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
            // registerANumericUpDown
            // 
            registerANumericUpDown.Hexadecimal = true;
            registerANumericUpDown.Location = new Point(566, 188);
            registerANumericUpDown.Maximum = new decimal(new int[] { 255, 0, 0, 0 });
            registerANumericUpDown.Name = "registerANumericUpDown";
            registerANumericUpDown.Size = new Size(60, 23);
            registerANumericUpDown.TabIndex = 18;
            // 
            // registerFNumericUpDown
            // 
            registerFNumericUpDown.Hexadecimal = true;
            registerFNumericUpDown.Location = new Point(632, 188);
            registerFNumericUpDown.Maximum = new decimal(new int[] { 255, 0, 0, 0 });
            registerFNumericUpDown.Name = "registerFNumericUpDown";
            registerFNumericUpDown.Size = new Size(60, 23);
            registerFNumericUpDown.TabIndex = 19;
            // 
            // button4
            // 
            button4.Location = new Point(639, 233);
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
            button5.Location = new Point(231, 306);
            button5.Name = "button5";
            button5.Size = new Size(66, 23);
            button5.TabIndex = 25;
            button5.Text = "check";
            button5.UseVisualStyleBackColor = true;
            button5.Click += button5_Click;
            // 
            // MainForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(button5);
            Controls.Add(addressLabel);
            Controls.Add(checkAddressButton);
            Controls.Add(checkAddressNumericUpDown);
            Controls.Add(rawPanel);
            Controls.Add(button4);
            Controls.Add(registerFNumericUpDown);
            Controls.Add(registerANumericUpDown);
            Controls.Add(pulseClockButton);
            Controls.Add(refreshRegistersButton);
            Controls.Add(label6);
            Controls.Add(label5);
            Controls.Add(label4);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(registerPCNumericUpDown);
            Controls.Add(registerSPNumericUpDown);
            Controls.Add(registerHLNumericUpDown);
            Controls.Add(registerDENumericUpDown);
            Controls.Add(registerBCNumericUpDown);
            Controls.Add(registerAFNumericUpDown);
            Controls.Add(button2);
            Controls.Add(button1);
            Controls.Add(viewPanel);
            DoubleBuffered = true;
            Name = "MainForm";
            Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)registerAFNumericUpDown).EndInit();
            ((System.ComponentModel.ISupportInitialize)registerBCNumericUpDown).EndInit();
            ((System.ComponentModel.ISupportInitialize)registerDENumericUpDown).EndInit();
            ((System.ComponentModel.ISupportInitialize)registerHLNumericUpDown).EndInit();
            ((System.ComponentModel.ISupportInitialize)registerSPNumericUpDown).EndInit();
            ((System.ComponentModel.ISupportInitialize)registerPCNumericUpDown).EndInit();
            ((System.ComponentModel.ISupportInitialize)registerANumericUpDown).EndInit();
            ((System.ComponentModel.ISupportInitialize)registerFNumericUpDown).EndInit();
            ((System.ComponentModel.ISupportInitialize)checkAddressNumericUpDown).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Panel viewPanel;
        private Button button1;
        private Button button2;
        private NumericUpDown registerAFNumericUpDown;
        private NumericUpDown registerBCNumericUpDown;
        private NumericUpDown registerDENumericUpDown;
        private NumericUpDown registerHLNumericUpDown;
        private NumericUpDown registerSPNumericUpDown;
        private NumericUpDown registerPCNumericUpDown;
        private Label label1;
        private Label label2;
        private Label label3;
        private Label label4;
        private Label label5;
        private Label label6;
        private Button refreshRegistersButton;
        private Button pulseClockButton;
        private NumericUpDown registerANumericUpDown;
        private NumericUpDown registerFNumericUpDown;
        private Button button4;
        private Panel rawPanel;
        private NumericUpDown checkAddressNumericUpDown;
        private Button checkAddressButton;
        private Label addressLabel;
        private Button button5;
    }
}
