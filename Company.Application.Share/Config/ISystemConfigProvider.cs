using Company.Hardware.Camera;
using Company.Hardware.ControlCard;
using Company.Hardware.Detector;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Company.Application.Share.Config
{
    /// <summary>
    /// 系统配置提供者
    /// </summary>
    public interface ISystemConfigProvider : ISoftwareConfigProvider, ICameraConfigProvider, IDetectorConfigProvider,IControlCardConfigProvider
    {
    }
}
