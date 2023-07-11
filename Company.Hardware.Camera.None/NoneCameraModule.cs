using Company.Core.Extension;
using Prism.Ioc;
using Prism.Modularity;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Media3D;

namespace Company.Hardware.Camera.None
{
    public class NoneCameraModule : IModule
    {
        public void OnInitialized(IContainerProvider containerProvider)
        {
            containerProvider.InitializeAssembly(Assembly.GetExecutingAssembly());
        }

        public void RegisterTypes(IContainerRegistry containerRegistry)
        {
            containerRegistry.RegisterAssembly(Assembly.GetExecutingAssembly());

            if (!containerRegistry.IsRegistered<ICamera>())
            {
                containerRegistry.RegisterSingleton<ICamera, NoneCamera>();//注册仿真相机到IOC容器中
            }
        }
    }
}
