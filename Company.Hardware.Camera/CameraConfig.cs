using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Company.Hardware.Camera
{
    /// <summary>
    /// 相机参数
    /// </summary>
    public class CameraConfig
    {

        public string Photo { get; set; } = "1.jpg";


        /// <summary>
        /// 相机宽度
        /// </summary>
        public int Width { get; set; } = 2644;

        /// <summary>
        /// 相机高度
        /// </summary>
        public int Height { get; set; } = 2041;

    }
}
