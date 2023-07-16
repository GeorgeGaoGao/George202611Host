using System;
using System.Collections.Generic;
using System.ComponentModel;
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
        [DisplayName("图像宽度")]
        public int Width { get; set; } = 1500;

        [DisplayName("图像高度")]
        public int Height { get; set; } = 1500;

        [DisplayName("默认图像")]
        public string Photo { get; set; } = "1.tif";

        [DisplayName("是否开启使用")]
        public bool IsActive { get; set; } = true;
    }
}
