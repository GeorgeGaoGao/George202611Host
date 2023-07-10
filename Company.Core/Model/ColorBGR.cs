using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Company.Core.Model
{
    /// <summary>
    /// 24位彩色图结构体
    /// </summary>
    public struct ColorBGR
    {
        public byte B { get; }
        public byte G { get; }
        public byte R { get; }
        public ColorBGR(byte r, byte g, byte b)
        {
            B = b;
            G = g;
            R = r;
        }
    }
}
