namespace EmulatorGUI
{
    partial class EmulatorForm
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
            menuStrip1 = new MenuStrip();
            fileToolStripMenuItem = new ToolStripMenuItem();
            openRomToolStripMenuItem = new ToolStripMenuItem();
            exitToolStripMenuItem = new ToolStripMenuItem();
            emulationToolStripMenuItem = new ToolStripMenuItem();
            resetToolStripMenuItem = new ToolStripMenuItem();
            shutdownToolStripMenuItem = new ToolStripMenuItem();
            configureToolStripMenuItem = new ToolStripMenuItem();
            toolStripSeparator1 = new ToolStripSeparator();
            insertToolStripMenuItem = new ToolStripMenuItem();
            insertGameCartridgeToolStripMenuItem = new ToolStripMenuItem();
            insertLinkCableToolStripMenuItem = new ToolStripMenuItem();
            removeToolStripMenuItem = new ToolStripMenuItem();
            removeGameCartridgeToolStripMenuItem = new ToolStripMenuItem();
            removeLinkCableToolStripMenuItem = new ToolStripMenuItem();
            toolStripSeparator2 = new ToolStripSeparator();
            resumeToolStripMenuItem = new ToolStripMenuItem();
            pauseToolStripMenuItem = new ToolStripMenuItem();
            nextFrameToolStripMenuItem = new ToolStripMenuItem();
            nextCycleToolStripMenuItem = new ToolStripMenuItem();
            inputToolStripMenuItem = new ToolStripMenuItem();
            aboutToolStripMenuItem = new ToolStripMenuItem();
            renderPanel = new Panel();
            saveStateToolStripMenuItem = new ToolStripMenuItem();
            loadStateToolStripMenuItem = new ToolStripMenuItem();
            menuStrip1.SuspendLayout();
            SuspendLayout();
            // 
            // menuStrip1
            // 
            menuStrip1.Items.AddRange(new ToolStripItem[] { fileToolStripMenuItem, emulationToolStripMenuItem, inputToolStripMenuItem, aboutToolStripMenuItem });
            menuStrip1.Location = new Point(0, 0);
            menuStrip1.Name = "menuStrip1";
            menuStrip1.Size = new Size(800, 24);
            menuStrip1.TabIndex = 0;
            menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            fileToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { openRomToolStripMenuItem, saveStateToolStripMenuItem, loadStateToolStripMenuItem, exitToolStripMenuItem });
            fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            fileToolStripMenuItem.Size = new Size(37, 20);
            fileToolStripMenuItem.Text = "File";
            // 
            // openRomToolStripMenuItem
            // 
            openRomToolStripMenuItem.Name = "openRomToolStripMenuItem";
            openRomToolStripMenuItem.Size = new Size(180, 22);
            openRomToolStripMenuItem.Text = "Open Rom...";
            openRomToolStripMenuItem.Click += openRomToolStripMenuItem_Click;
            // 
            // exitToolStripMenuItem
            // 
            exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            exitToolStripMenuItem.ShortcutKeys = Keys.Alt | Keys.F4;
            exitToolStripMenuItem.Size = new Size(180, 22);
            exitToolStripMenuItem.Text = "Exit";
            exitToolStripMenuItem.Click += exitToolStripMenuItem_Click;
            // 
            // emulationToolStripMenuItem
            // 
            emulationToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { resetToolStripMenuItem, shutdownToolStripMenuItem, configureToolStripMenuItem, toolStripSeparator1, insertToolStripMenuItem, removeToolStripMenuItem, toolStripSeparator2, resumeToolStripMenuItem, pauseToolStripMenuItem, nextFrameToolStripMenuItem, nextCycleToolStripMenuItem });
            emulationToolStripMenuItem.Name = "emulationToolStripMenuItem";
            emulationToolStripMenuItem.Size = new Size(73, 20);
            emulationToolStripMenuItem.Text = "Emulation";
            // 
            // resetToolStripMenuItem
            // 
            resetToolStripMenuItem.Name = "resetToolStripMenuItem";
            resetToolStripMenuItem.Size = new Size(180, 22);
            resetToolStripMenuItem.Text = "Reset";
            resetToolStripMenuItem.ToolTipText = "Resets the emulation";
            resetToolStripMenuItem.Click += resetToolStripMenuItem_Click;
            // 
            // shutdownToolStripMenuItem
            // 
            shutdownToolStripMenuItem.Name = "shutdownToolStripMenuItem";
            shutdownToolStripMenuItem.Size = new Size(180, 22);
            shutdownToolStripMenuItem.Text = "Shutdown";
            shutdownToolStripMenuItem.ToolTipText = "Stops all emulation";
            shutdownToolStripMenuItem.Click += shutdownToolStripMenuItem_Click;
            // 
            // configureToolStripMenuItem
            // 
            configureToolStripMenuItem.Name = "configureToolStripMenuItem";
            configureToolStripMenuItem.Size = new Size(180, 22);
            configureToolStripMenuItem.Text = "Configure";
            configureToolStripMenuItem.Click += configureToolStripMenuItem_Click;
            // 
            // toolStripSeparator1
            // 
            toolStripSeparator1.Name = "toolStripSeparator1";
            toolStripSeparator1.Size = new Size(177, 6);
            // 
            // insertToolStripMenuItem
            // 
            insertToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { insertGameCartridgeToolStripMenuItem, insertLinkCableToolStripMenuItem });
            insertToolStripMenuItem.Name = "insertToolStripMenuItem";
            insertToolStripMenuItem.Size = new Size(180, 22);
            insertToolStripMenuItem.Text = "Insert";
            // 
            // insertGameCartridgeToolStripMenuItem
            // 
            insertGameCartridgeToolStripMenuItem.Name = "insertGameCartridgeToolStripMenuItem";
            insertGameCartridgeToolStripMenuItem.Size = new Size(157, 22);
            insertGameCartridgeToolStripMenuItem.Text = "Game Cartridge";
            insertGameCartridgeToolStripMenuItem.Click += insertGameCartridgeToolStripMenuItem_Click;
            // 
            // insertLinkCableToolStripMenuItem
            // 
            insertLinkCableToolStripMenuItem.Name = "insertLinkCableToolStripMenuItem";
            insertLinkCableToolStripMenuItem.Size = new Size(157, 22);
            insertLinkCableToolStripMenuItem.Text = "Link Cable";
            insertLinkCableToolStripMenuItem.Click += insertLinkCableToolStripMenuItem_Click;
            // 
            // removeToolStripMenuItem
            // 
            removeToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { removeGameCartridgeToolStripMenuItem, removeLinkCableToolStripMenuItem });
            removeToolStripMenuItem.Name = "removeToolStripMenuItem";
            removeToolStripMenuItem.Size = new Size(180, 22);
            removeToolStripMenuItem.Text = "Remove";
            // 
            // removeGameCartridgeToolStripMenuItem
            // 
            removeGameCartridgeToolStripMenuItem.Name = "removeGameCartridgeToolStripMenuItem";
            removeGameCartridgeToolStripMenuItem.Size = new Size(157, 22);
            removeGameCartridgeToolStripMenuItem.Text = "Game Cartridge";
            removeGameCartridgeToolStripMenuItem.ToolTipText = "Simulates removing the Game Cartridge";
            removeGameCartridgeToolStripMenuItem.Click += removeGameCartridgeToolStripMenuItem_Click;
            // 
            // removeLinkCableToolStripMenuItem
            // 
            removeLinkCableToolStripMenuItem.Name = "removeLinkCableToolStripMenuItem";
            removeLinkCableToolStripMenuItem.Size = new Size(157, 22);
            removeLinkCableToolStripMenuItem.Text = "Link Cable";
            removeLinkCableToolStripMenuItem.Click += removeLinkCableToolStripMenuItem_Click;
            // 
            // toolStripSeparator2
            // 
            toolStripSeparator2.Name = "toolStripSeparator2";
            toolStripSeparator2.Size = new Size(177, 6);
            // 
            // resumeToolStripMenuItem
            // 
            resumeToolStripMenuItem.Name = "resumeToolStripMenuItem";
            resumeToolStripMenuItem.Size = new Size(180, 22);
            resumeToolStripMenuItem.Text = "Resume";
            resumeToolStripMenuItem.ToolTipText = "Resumes the clock";
            resumeToolStripMenuItem.Click += resumeToolStripMenuItem_Click;
            // 
            // pauseToolStripMenuItem
            // 
            pauseToolStripMenuItem.Name = "pauseToolStripMenuItem";
            pauseToolStripMenuItem.Size = new Size(180, 22);
            pauseToolStripMenuItem.Text = "Pause";
            pauseToolStripMenuItem.ToolTipText = "Pauses the clock";
            pauseToolStripMenuItem.Click += pauseToolStripMenuItem_Click;
            // 
            // nextFrameToolStripMenuItem
            // 
            nextFrameToolStripMenuItem.Name = "nextFrameToolStripMenuItem";
            nextFrameToolStripMenuItem.Size = new Size(180, 22);
            nextFrameToolStripMenuItem.Text = "Next Frame";
            nextFrameToolStripMenuItem.ToolTipText = "Resumes the clock until V-Sync";
            nextFrameToolStripMenuItem.Click += nextFrameToolStripMenuItem_Click;
            // 
            // nextCycleToolStripMenuItem
            // 
            nextCycleToolStripMenuItem.Name = "nextCycleToolStripMenuItem";
            nextCycleToolStripMenuItem.Size = new Size(180, 22);
            nextCycleToolStripMenuItem.Text = "Next Cycle";
            nextCycleToolStripMenuItem.ToolTipText = "Runs the processor until the next instruction";
            nextCycleToolStripMenuItem.Click += nextCycleToolStripMenuItem_Click;
            // 
            // inputToolStripMenuItem
            // 
            inputToolStripMenuItem.Name = "inputToolStripMenuItem";
            inputToolStripMenuItem.Size = new Size(47, 20);
            inputToolStripMenuItem.Text = "Input";
            // 
            // aboutToolStripMenuItem
            // 
            aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            aboutToolStripMenuItem.Size = new Size(52, 20);
            aboutToolStripMenuItem.Text = "About";
            // 
            // renderPanel
            // 
            renderPanel.Location = new Point(12, 36);
            renderPanel.Name = "renderPanel";
            renderPanel.Size = new Size(405, 341);
            renderPanel.TabIndex = 1;
            // 
            // saveStateToolStripMenuItem
            // 
            saveStateToolStripMenuItem.Name = "saveStateToolStripMenuItem";
            saveStateToolStripMenuItem.Size = new Size(180, 22);
            saveStateToolStripMenuItem.Text = "Save State";
            // 
            // loadStateToolStripMenuItem
            // 
            loadStateToolStripMenuItem.Name = "loadStateToolStripMenuItem";
            loadStateToolStripMenuItem.Size = new Size(140, 22);
            loadStateToolStripMenuItem.Text = "Load State";
            // 
            // EmulatorForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(renderPanel);
            Controls.Add(menuStrip1);
            MainMenuStrip = menuStrip1;
            Name = "EmulatorForm";
            Text = "Kitsemu";
            Load += EmulatorForm_Load;
            menuStrip1.ResumeLayout(false);
            menuStrip1.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private MenuStrip menuStrip1;
        private ToolStripMenuItem fileToolStripMenuItem;
        private ToolStripMenuItem openRomToolStripMenuItem;
        private ToolStripMenuItem exitToolStripMenuItem;
        private ToolStripMenuItem emulationToolStripMenuItem;
        private Panel renderPanel;
        private ToolStripMenuItem resetToolStripMenuItem;
        private ToolStripMenuItem shutdownToolStripMenuItem;
        private ToolStripSeparator toolStripSeparator1;
        private ToolStripMenuItem removeToolStripMenuItem;
        private ToolStripMenuItem removeGameCartridgeToolStripMenuItem;
        private ToolStripMenuItem pauseToolStripMenuItem;
        private ToolStripMenuItem nextFrameToolStripMenuItem;
        private ToolStripMenuItem nextCycleToolStripMenuItem;
        private ToolStripSeparator toolStripSeparator2;
        private ToolStripMenuItem configureToolStripMenuItem;
        private ToolStripMenuItem insertToolStripMenuItem;
        private ToolStripMenuItem insertGameCartridgeToolStripMenuItem;
        private ToolStripMenuItem resumeToolStripMenuItem;
        private ToolStripMenuItem inputToolStripMenuItem;
        private ToolStripMenuItem insertLinkCableToolStripMenuItem;
        private ToolStripMenuItem removeLinkCableToolStripMenuItem;
        private ToolStripMenuItem aboutToolStripMenuItem;
        private ToolStripMenuItem saveStateToolStripMenuItem;
        private ToolStripMenuItem loadStateToolStripMenuItem;
    }
}