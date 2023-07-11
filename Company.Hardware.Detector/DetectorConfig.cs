using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Company.Hardware.Detector
{
    /// <summary>
    /// FPD=平板探测器配置参数
    /// </summary>
    public class DetectorConfig
    {
        public int Width { get; set; } = 1500;
        public int Height { get; set; } = 1500;
        public string Photo { get; set; } = "1.tif";
    }
}
