using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Company.Hardware.Detector
{
    /// <summary>
    /// 平板探测器配置提供者
    /// </summary>
    public interface IDetectorConfigProvider
    {
        /// <summary>
        /// 平板探测器参数
        /// </summary>
        DetectorConfig DetectorConfig { get; }

        /// <summary>
        /// 参数改变事件
        /// </summary>
        event Action OnChanged;
    }
}
