namespace EmulatorGUI.EmulatorLib
{
    partial class ProcessorRegisterViewControl
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
            registerNameLabel = new Label();
            registerValueNumericUpDown = new NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)registerValueNumericUpDown).BeginInit();
            SuspendLayout();
            // 
            // registerNameLabel
            // 
            registerNameLabel.AutoSize = true;
            registerNameLabel.Font = new Font("Consolas", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            registerNameLabel.Location = new Point(3, 2);
            registerNameLabel.Name = "registerNameLabel";
            registerNameLabel.Size = new Size(28, 14);
            registerNameLabel.TabIndex = 0;
            registerNameLabel.Text = "AF:";
            // 
            // registerValueNumericUpDown
            // 
            registerValueNumericUpDown.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            registerValueNumericUpDown.Font = new Font("Consolas", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            registerValueNumericUpDown.Hexadecimal = true;
            registerValueNumericUpDown.Location = new Point(37, 0);
            registerValueNumericUpDown.Maximum = new decimal(new int[] { 65535, 0, 0, 0 });
            registerValueNumericUpDown.Name = "registerValueNumericUpDown";
            registerValueNumericUpDown.Size = new Size(212, 22);
            registerValueNumericUpDown.TabIndex = 1;
            registerValueNumericUpDown.ValueChanged += registerValueNumericUpDown_ValueChanged;
            // 
            // ProcessorRegisterViewControl
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            Controls.Add(registerValueNumericUpDown);
            Controls.Add(registerNameLabel);
            Name = "ProcessorRegisterViewControl";
            Size = new Size(249, 22);
            Load += ProcessorRegisterViewControl_Load;
            ((System.ComponentModel.ISupportInitialize)registerValueNumericUpDown).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label registerNameLabel;
        private NumericUpDown registerValueNumericUpDown;
    }
}
