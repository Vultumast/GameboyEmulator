using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
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

        private string headerString = "ADDR 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F";

        private bool paintRun = false;

        private SizeF fontSize = new SizeF(0, 0);
        private float conversionRatio = 0;
        private float descentSize = 0;
        private float uiSize = 0;


        private void HexViewControl_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.Clear(BackColor);

            using Font consolas = new Font(Font.FontFamily, 13, FontStyle.Regular, GraphicsUnit.Pixel);

            fontSize = e.Graphics.MeasureString("A", consolas, 255, StringFormat.GenericTypographic);

            conversionRatio = consolas.Size / (float)consolas.FontFamily.GetEmHeight(FontStyle.Regular);

            descentSize = (consolas.FontFamily.GetCellDescent(FontStyle.Regular) * conversionRatio);

            uiSize = (fontSize.Width * 4) + (descentSize * 2);

            e.Graphics.FillRectangle(SystemBrushes.ControlDark, 0, 0, Width, uiSize);
            e.Graphics.FillRectangle(SystemBrushes.ControlDark, 0, 0, uiSize, Height);

            drawString(headerString, descentSize, (uiSize - fontSize.Height), Brushes.Blue);

            for (var i = 0; i < 0xFFFF; i += 0xF)
            {
                var offsetX = i / 0xF;

                var drawY = (((offsetX + 1) * fontSize.Width) * 3) + fontSize.Width * 3;

                if (drawY > Height)
                    break;
                drawString(String.Format("{0:X04}", i, 0), descentSize, drawY, Brushes.Blue);
                drawString(String.Format("{0:X02} {0:X02} {0:X02} {0:X02} {0:X02} {0:X02} {0:X02} {0:X02} {0:X02} {0:X02} {0:X02} {0:X02} {0:X02} {0:X02} {0:X02} {0:X02}", 0), uiSize + descentSize, drawY, Brushes.Black);

            }

            paintRun = true;

            return;

            void drawString(string value, float x, float y, Brush brush) => e.Graphics.DrawString(value, consolas, brush, x, y, StringFormat.GenericTypographic);
        }

        private void HexViewControl_MouseMove(object sender, MouseEventArgs e)
        {
            if (!paintRun)
                return;

            RectangleF[] rects = new RectangleF[0xF];

            /* for (var i = 0; i < rects.Length; i++)
            {
                RectangleF rect = new RectangleF(uiSize, uiSize, );
            }
            */

        }
    }
}
