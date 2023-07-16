using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Company.Hardware.Camera
{
    /// <summary>
    /// 相机配置提供者
    /// </summary>
    public interface ICameraConfigProvider
    {
        /// <summary>
        /// 相机参数
        /// </summary>
        CameraConfig CameraConfig { get; }

        /// <summary>
        /// 参数改变事件
        /// </summary>
        event Action OnChanged;
    }
}
