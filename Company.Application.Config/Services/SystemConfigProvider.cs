using Company.Application.Share.Config;
using Company.Core.Ioc;
using Company.Hardware.Camera;
using Company.Hardware.Detector;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Company.Application.Config.Services
{
    /// <summary>
    /// 系统配置提供者，作用是将系统配置参数传给不同的模块，用接口实现数据通讯
    /// </summary>
    [ExposedService(Lifetime.Singleton, typeof(ISystemConfigProvider), typeof(ISoftwareConfigProvider), typeof(ICameraConfigProvider), typeof(IDetectorConfigProvider))]
    public class SystemConfigProvider : ISystemConfigProvider, ISoftwareConfigProvider, ICameraConfigProvider, IDetectorConfigProvider
    {
        private readonly SystemConfigManager SystemConfigManager;
        public SystemConfigProvider(SystemConfigManager systemConfigManager) 
        {
            SystemConfigManager = systemConfigManager;
            Initialize();

        }

        private void Initialize()
        {
            SoftwareConfig = SystemConfigManager.Config.SoftwareConfig;
            CameraConfig = SystemConfigManager.Config.CameraConfig;
            DetectorConfig = SystemConfigManager.Config.DetectorConfig;
        }

        internal void Invoke()
        {
            OnChanged?.Invoke();
        }

        public SoftwareConfig SoftwareConfig { get; set; }

        public CameraConfig CameraConfig { get; set; }

        public DetectorConfig DetectorConfig { get; set; }

        public event Action OnChanged;
    }
}
