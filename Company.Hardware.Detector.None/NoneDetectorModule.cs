using Company.Core.Extension;
using Prism.Ioc;
using Prism.Modularity;
using Splat;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Company.Hardware.Detector.None
{
    public class NoneDetectorModule : IModule
    {
        public void OnInitialized(IContainerProvider containerProvider)
        {
            containerProvider.InitializeAssembly(Assembly.GetExecutingAssembly());
        }

        public void RegisterTypes(IContainerRegistry containerRegistry)
        {
            containerRegistry.RegisterAssembly(Assembly.GetExecutingAssembly());

            if (!containerRegistry.IsRegistered<IDetector>())
            {
                containerRegistry.RegisterSingleton<IDetector, NoneDetector>();//注册仿真FPD到IOC容器中
            }
        }
    }
}
