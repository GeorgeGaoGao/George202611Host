using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Company.Core.Model
{
    /// <summary>
    /// 32位彩图结构体
    /// </summary>
    public struct ColorBGRA
    {
        public byte B { get; }
        public byte G { get; }
        public byte R { get; }
        public byte A { get; }
        public ColorBGRA(byte a ,byte r, byte g, byte b)
        {
            B = b;
            G = g;
            R = r;
            A = a;
        }
    }
}
