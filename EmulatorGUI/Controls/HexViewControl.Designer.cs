namespace EmulatorGUI.Controls
{
    partial class HexViewControl
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            vScrollBar = new VScrollBar();
            infoGroupBox = new GroupBox();
            opcodeLabel = new Label();
            int16Label = new Label();
            uint16Label = new Label();
            int8Label = new Label();
            uint8Label = new Label();
            binaryLabel = new Label();
            prefixedLabel = new Label();
            infoGroupBox.SuspendLayout();
            SuspendLayout();
            // 
            // vScrollBar
            // 
            vScrollBar.Dock = DockStyle.Right;
            vScrollBar.Location = new Point(519, 0);
            vScrollBar.Maximum = 819;
            vScrollBar.Name = "vScrollBar";
            vScrollBar.Size = new Size(17, 200);
            vScrollBar.TabIndex = 0;
            vScrollBar.ValueChanged += vScrollBar_ValueChanged;
            // 
            // infoGroupBox
            // 
            infoGroupBox.Controls.Add(prefixedLabel);
            infoGroupBox.Controls.Add(opcodeLabel);
            infoGroupBox.Controls.Add(int16Label);
            infoGroupBox.Controls.Add(uint16Label);
            infoGroupBox.Controls.Add(int8Label);
            infoGroupBox.Controls.Add(uint8Label);
            infoGroupBox.Controls.Add(binaryLabel);
            infoGroupBox.Dock = DockStyle.Bottom;
            infoGroupBox.Location = new Point(0, 200);
            infoGroupBox.Name = "infoGroupBox";
            infoGroupBox.Size = new Size(536, 100);
            infoGroupBox.TabIndex = 1;
            infoGroupBox.TabStop = false;
            infoGroupBox.Text = "Info";
            // 
            // opcodeLabel
            // 
            opcodeLabel.AutoSize = true;
            opcodeLabel.Location = new Point(131, 18);
            opcodeLabel.Name = "opcodeLabel";
            opcodeLabel.Size = new Size(84, 14);
            opcodeLabel.TabIndex = 2;
            opcodeLabel.Text = "OpCode: NOP";
            // 
            // int16Label
            // 
            int16Label.AutoSize = true;
            int16Label.Location = new Point(6, 74);
            int16Label.Name = "int16Label";
            int16Label.Size = new Size(63, 14);
            int16Label.TabIndex = 5;
            int16Label.Text = "int16: 0";
            // 
            // uint16Label
            // 
            uint16Label.AutoSize = true;
            uint16Label.Location = new Point(6, 60);
            uint16Label.Name = "uint16Label";
            uint16Label.Size = new Size(70, 14);
            uint16Label.TabIndex = 4;
            uint16Label.Text = "uint16: 0";
            // 
            // int8Label
            // 
            int8Label.AutoSize = true;
            int8Label.Location = new Point(6, 46);
            int8Label.Name = "int8Label";
            int8Label.Size = new Size(56, 14);
            int8Label.TabIndex = 3;
            int8Label.Text = "int8: 0";
            // 
            // uint8Label
            // 
            uint8Label.AutoSize = true;
            uint8Label.Location = new Point(6, 32);
            uint8Label.Name = "uint8Label";
            uint8Label.Size = new Size(63, 14);
            uint8Label.TabIndex = 2;
            uint8Label.Text = "uint8: 0";
            // 
            // binaryLabel
            // 
            binaryLabel.AutoSize = true;
            binaryLabel.Location = new Point(6, 18);
            binaryLabel.Name = "binaryLabel";
            binaryLabel.Size = new Size(119, 14);
            binaryLabel.TabIndex = 0;
            binaryLabel.Text = "Binary: 00000000";
            // 
            // prefixedLabel
            // 
            prefixedLabel.AutoSize = true;
            prefixedLabel.Location = new Point(131, 32);
            prefixedLabel.Name = "prefixedLabel";
            prefixedLabel.Size = new Size(112, 14);
            prefixedLabel.TabIndex = 6;
            prefixedLabel.Text = "Prefixed: RLC B";
            // 
            // HexViewControl
            // 
            AutoScaleDimensions = new SizeF(7F, 14F);
            AutoScaleMode = AutoScaleMode.Font;
            Controls.Add(vScrollBar);
            Controls.Add(infoGroupBox);
            DoubleBuffered = true;
            Font = new Font("Consolas", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            Name = "HexViewControl";
            Size = new Size(536, 300);
            Load += HexViewControl_Load;
            Paint += HexViewControl_Paint;
            MouseDown += HexViewControl_MouseDown;
            MouseMove += HexViewControl_MouseMove;
            Resize += HexViewControl_Resize;
            infoGroupBox.ResumeLayout(false);
            infoGroupBox.PerformLayout();
            ResumeLayout(false);
        }

        #endregion

        private VScrollBar vScrollBar;
        private GroupBox infoGroupBox;
        private Label binaryLabel;
        private Label int8Label;
        private Label uint8Label;
        private Label int16Label;
        private Label uint16Label;
        private Label opcodeLabel;
        private Label prefixedLabel;
    }
}
