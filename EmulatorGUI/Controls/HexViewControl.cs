using EmulatorGUI.EmulatorLib;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace EmulatorGUI.Controls
{
    public partial class HexViewControl : UserControl
    {
        public HexViewControl()
        {
            InitializeComponent();
        }

        private bool paintRun = false;

        private SizeF fontSize = new SizeF(0, 0);
        private float conversionRatio = 0;
        private float descentSize = 0;
        private float uiSize = 0;

        private float drawOffsetY = 0;

        private float lineSize => fontSize.Width * 3;

        private ushort _selectedAddress = 0;
        public ushort SelectedAddress
        {
            get => _selectedAddress;
            set
            {
                if (_selectedAddress != value)
                    Invalidate();

                _selectedAddress = value;
                infoGroupBox.Text = $"Info - {_selectedAddress.ToString("X04")}";
            }
        }

        private ushort _pcAddress = 0;
        public ushort PCAddress
        {
            get => _pcAddress;
            set
            {
                if (_pcAddress != value)
                    Invalidate();

                _pcAddress = value;
            }
        }


        private Point _hotTrackPosition = Point.Empty;
        public Point HotTrackPosition
        {
            get => _hotTrackPosition;
            set
            {
                Point nextTrue = new(Math.Clamp(value.X, 0x00, 0xF), Math.Clamp(value.Y, 0x00, 0xFFF));

                if (nextTrue != _hotTrackPosition)
                {
                    _hotTrackPosition = nextTrue;
                    Invalidate();
                }
            }
        }

        MemoryBus? _memoryBus = null;

        public MemoryBus? MemoryBus
        {
            get => _memoryBus;
            set
            {
                _memoryBus = value;
                UpdateInfo();
                Invalidate();
            }
        }


        private void HexViewControl_Load(object sender, EventArgs e)
        {
            Invalidate();
        }

        private void HexViewControl_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.Clear(BackColor);

            e.Graphics.PixelOffsetMode = System.Drawing.Drawing2D.PixelOffsetMode.HighQuality;

            using Font consolas = new Font(Font.FontFamily, 13, FontStyle.Regular, GraphicsUnit.Pixel);

            fontSize = e.Graphics.MeasureString("A", consolas, 255, StringFormat.GenericTypographic);

            conversionRatio = consolas.Size / (float)consolas.FontFamily.GetEmHeight(FontStyle.Regular);

            descentSize = (consolas.FontFamily.GetCellDescent(FontStyle.Regular) * conversionRatio);

            uiSize = (fontSize.Width * 4) + (descentSize * 2);

            e.Graphics.FillRectangle(SystemBrushes.ControlDark, 0, 0, uiSize, Height);

            int lineStart = Math.Clamp(((int)((drawOffsetY - 1) / lineSize)) * 0x10, 0, 0xFFFF);
            int sidebarStartX = (int)((uiSize + descentSize) + (0x10 * lineSize) + (lineSize * 0.5f));

            for (var i = lineStart; i < 0xFFFF; i += 0x10)
            {
                if (i < 0)
                    continue;

                var offsetX = i / 0x10;

                var drawY = ((float)(offsetX + 2) * lineSize) - drawOffsetY;

                if (drawY > Height)
                    break;

                drawString(String.Format("{0:X04}", i, 0), descentSize, drawY, Brushes.Blue);

                int finalY = (int)drawY;

                for (var r = 0; r < 0x10; r++)
                {
                    int finalX = (int)((uiSize + descentSize) + (r * lineSize));

                    ushort address = (ushort)(i + r);
                    byte value = MemoryBus?.Read(address) ?? 0;

                    char c = '.';
                    if (value < 0x20)
                        c = '.';
                    else
                        c = (char)value;

                    Pen BGPen = SystemPens.Control;
                    Brush BGBrush = SystemBrushes.Control;
                    Brush textBrush = Brushes.Black;

                    if (address == SelectedAddress)
                    {
                        BGBrush = SystemBrushes.Highlight;
                        textBrush = SystemBrushes.HighlightText;
                    }

                    if (offsetX == HotTrackPosition.Y && r == HotTrackPosition.X)
                        BGPen = SystemPens.HotTrack;
                    
                    if (address == PCAddress)
                    {
                        BGBrush = Brushes.Red;
                        textBrush = Brushes.White;
                    }

                    RectangleF mainBounds = new(finalX - 1.0f, finalY, (fontSize.Width * 2.0f) + 2.0f, fontSize.Height);
                    RectangleF sidebarBounds = new(sidebarStartX + (r * fontSize.Width), finalY, fontSize.Width - 1, fontSize.Height - 1);

                    if (BGBrush != SystemBrushes.Control)
                    {
                        e.Graphics.FillRectangle(BGBrush, mainBounds);
                        e.Graphics.FillRectangle(BGBrush, sidebarBounds);
                    }

                    if (BGPen != SystemPens.Control)
                    {
                        e.Graphics.DrawRectangle(BGPen, mainBounds);
                        e.Graphics.DrawRectangle(BGPen, sidebarBounds);
                    }

                    drawString(string.Format("{0:X02}", value), finalX, finalY, textBrush);
                    drawString(c.ToString(), sidebarStartX + (r * fontSize.Width), finalY, textBrush);

                }
            }

            drawTopBar();


            // using Font half = new Font(consolas.FontFamily, 10, FontStyle.Bold, GraphicsUnit.Pixel);

            // e.Graphics.DrawString("ROM BANK 0", half, Brushes.Red, lineSize * 1.625f, lineSize * 1.625f);

            paintRun = true;

            return;

            void drawString(string value, float x, float y, Brush brush) => e.Graphics.DrawString(value, consolas, brush, x, y, StringFormat.GenericTypographic);

            void drawTopBar()
            {
                e.Graphics.FillRectangle(SystemBrushes.ControlDark, 0, 0, Width, uiSize);
                drawString("ADDR", descentSize, (uiSize - fontSize.Height), Brushes.Blue);
                for (var r = 0; r < 0x10; r++)
                    drawString(string.Format("{0:X02}", r), (int)((uiSize + descentSize) + (r * lineSize)), (int)(uiSize - fontSize.Height), Brushes.Blue);

                drawString("Text", (int)((uiSize + descentSize) + (0x11 * lineSize)), (int)(uiSize - fontSize.Height), Brushes.Blue);
            }

        }

        private void HexViewControl_MouseMove(object sender, MouseEventArgs e)
        {
            if (!paintRun)
                return;

            HotTrackPosition = new((int)((e.X - uiSize) / lineSize), (int)((e.Y - uiSize + drawOffsetY) / lineSize));

        }
        private void HexViewControl_MouseDown(object sender, MouseEventArgs e)
        {
            if (!paintRun)
                return;

            HotTrackPosition = new((int)((e.X - uiSize) / lineSize), (int)((e.Y - uiSize + drawOffsetY) / lineSize));

            ushort address = (ushort)((HotTrackPosition.Y * 0x10) + HotTrackPosition.X);

            if (e.Button == MouseButtons.Left)
            {
                SelectedAddress = address;

                UpdateInfo();
            }
        }

        private void HexViewControl_Resize(object sender, EventArgs e)
        {
            Invalidate();
        }


        private void vScrollBar_ValueChanged(object sender, EventArgs e)
        {
            float scrollRatio = (float)vScrollBar.Value / (float)(vScrollBar.Maximum - (vScrollBar.LargeChange - vScrollBar.SmallChange));

            float totalLineSize = (lineSize * (0xFFF + 3)) - (Height - infoGroupBox.Height);

            drawOffsetY = totalLineSize * scrollRatio;

            Invalidate();
        }


        private void UpdateInfo()
        {
            byte uint8 = MemoryBus?.Read(_selectedAddress) ?? 0;

            binaryLabel.Text = string.Format("Binary: {0:B08}", uint8);

            uint8Label.Text = $"uint8: {uint8}";
            int8Label.Text = $"int8: {(sbyte)uint8}";

            if (_selectedAddress < 0xFFFF)
            {
                ushort uint16 = uint8;
                uint16 |= (ushort)((MemoryBus?.Read((ushort)(_selectedAddress + 1)) ?? 0) << 8);

                uint16Label.Text = $"uint16: {uint16}";
                int16Label.Text = $"int16: {(short)uint16}";
            }
            else
            {
                uint16Label.Text = "uint16:";
                int16Label.Text = "int16:";
            }

            opcodeLabel.Text = $"OpCode: {OpCodeInfo.GetOpCodeInfo(uint8).ToString()}";
            prefixedLabel.Text = $"Prefixed: {OpCodeInfo.GetOpCodePrefixedInfo(uint8).ToString()}";
        }
    }
}
