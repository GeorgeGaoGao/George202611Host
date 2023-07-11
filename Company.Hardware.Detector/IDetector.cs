using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Company.Hardware.Detector
{
    /// <summary>
    /// 平板探测器接口
    /// </summary>
    public interface IDetector
    {
        event Action<DetectorImage> OnGrabbed;


        /// <summary>
        /// 表示平板探测器是否初始化完成
        /// </summary>
        bool Initialized { get; }

        /// <summary>
        /// 初始化平板探测器
        /// </summary>
        /// <returns></returns>
        bool Init(DetectorConfig config);

        /// <summary>
        /// 连续采集数据
        /// </summary>
        /// <returns></returns>
        bool Grab();

        /// <summary>
        /// 关闭平板探测器
        /// </summary>
        bool Close();
    }
}
