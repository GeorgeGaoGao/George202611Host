using Company.Core.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Company.Hardware.Camera
{
    /// <summary>
    /// 表示一张图像
    /// </summary>
    public struct Photo
    {
        /// <summary>
        /// 图像数据的指针
        /// </summary>
        public IntPtr Header { get; }

        /// <summary>
        /// 图像宽度
        /// </summary>
        public int Width { get; set; }

        /// <summary>
        /// 图像高度
        /// </summary>
        public int Height { get; set; }

        public int Length => Width * Height * Marshal.SizeOf(typeof(ColorBGRA));

        public Photo(UnmanagedArray2D<ColorBGRA> data)
        {
            Header = data.Header; 
            Width = data.Width;
            Height = data.Height;
        }
    }
}
