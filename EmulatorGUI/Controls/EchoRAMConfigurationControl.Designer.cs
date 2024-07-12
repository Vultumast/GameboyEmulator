namespace EmulatorGUI.Controls
{
    partial class EchoRAMConfigurationControl
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
            components = new System.ComponentModel.Container();
            mirrorRadioButton = new RadioButton();
            groupBox1 = new GroupBox();
            forcedNumericUpDown = new NumericUpDown();
            forcedRadioButton = new RadioButton();
            expansionRadioButton = new RadioButton();
            commonToolTip = new ToolTip(components);
            groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)forcedNumericUpDown).BeginInit();
            SuspendLayout();
            // 
            // mirrorRadioButton
            // 
            mirrorRadioButton.AutoSize = true;
            mirrorRadioButton.Checked = true;
            mirrorRadioButton.Location = new Point(6, 22);
            mirrorRadioButton.Name = "mirrorRadioButton";
            mirrorRadioButton.Size = new Size(58, 19);
            mirrorRadioButton.TabIndex = 0;
            mirrorRadioButton.TabStop = true;
            mirrorRadioButton.Text = "Mirror";
            commonToolTip.SetToolTip(mirrorRadioButton, "Echo RAM will behave as a mirror of normal RAM (Default)");
            mirrorRadioButton.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            groupBox1.AutoSize = true;
            groupBox1.AutoSizeMode = AutoSizeMode.GrowAndShrink;
            groupBox1.Controls.Add(forcedNumericUpDown);
            groupBox1.Controls.Add(forcedRadioButton);
            groupBox1.Controls.Add(expansionRadioButton);
            groupBox1.Controls.Add(mirrorRadioButton);
            groupBox1.Dock = DockStyle.Fill;
            groupBox1.Location = new Point(0, 0);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(174, 142);
            groupBox1.TabIndex = 1;
            groupBox1.TabStop = false;
            groupBox1.Text = "Echo RAM Configuration";
            // 
            // forcedNumericUpDown
            // 
            forcedNumericUpDown.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            forcedNumericUpDown.Hexadecimal = true;
            forcedNumericUpDown.Location = new Point(6, 97);
            forcedNumericUpDown.Maximum = new decimal(new int[] { 255, 0, 0, 0 });
            forcedNumericUpDown.Name = "forcedNumericUpDown";
            forcedNumericUpDown.Size = new Size(165, 23);
            forcedNumericUpDown.TabIndex = 3;
            // 
            // forcedRadioButton
            // 
            forcedRadioButton.AutoSize = true;
            forcedRadioButton.Location = new Point(6, 72);
            forcedRadioButton.Name = "forcedRadioButton";
            forcedRadioButton.Size = new Size(61, 19);
            forcedRadioButton.TabIndex = 2;
            forcedRadioButton.Text = "Forced";
            commonToolTip.SetToolTip(forcedRadioButton, "Regardless of read/writes, Echo RAM will be forced to be a specified value.");
            forcedRadioButton.UseVisualStyleBackColor = true;
            // 
            // expansionRadioButton
            // 
            expansionRadioButton.AutoSize = true;
            expansionRadioButton.Location = new Point(6, 47);
            expansionRadioButton.Name = "expansionRadioButton";
            expansionRadioButton.Size = new Size(79, 19);
            expansionRadioButton.TabIndex = 1;
            expansionRadioButton.Text = "Expansion";
            commonToolTip.SetToolTip(expansionRadioButton, "Echo RAM will be treated as additional memory space");
            expansionRadioButton.UseVisualStyleBackColor = true;
            // 
            // EchoRAMConfigurationControl
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            Controls.Add(groupBox1);
            Name = "EchoRAMConfigurationControl";
            Size = new Size(174, 142);
            groupBox1.ResumeLayout(false);
            groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)forcedNumericUpDown).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private RadioButton mirrorRadioButton;
        private ToolTip commonToolTip;
        private GroupBox groupBox1;
        private RadioButton forcedRadioButton;
        private RadioButton expansionRadioButton;
        private NumericUpDown forcedNumericUpDown;
    }
}
