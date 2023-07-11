using Company.Core.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Company.Hardware.Detector
{
    /// <summary>
    /// 平板探测器的图像数据
    /// </summary>
    public struct DetectorImage
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

        public int Length => Width * Height * Marshal.SizeOf(typeof(ushort));

        public DetectorImage(UnmanagedArray2D<ushort> data)
        {
            Header = data.Header;
            Width = data.Width;
            Height = data.Height;
        }
    }
}
