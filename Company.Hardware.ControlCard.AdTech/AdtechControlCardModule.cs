using Company.Core.Extension;
using Prism.Ioc;
using Prism.Modularity;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Company.Hardware.ControlCard.AdTech
{
    /// <summary>
    /// 众为兴模块
    /// </summary>
    public class AdtechControlCardModule : IModule
    {
        public void OnInitialized(IContainerProvider containerProvider)
        {
            containerProvider.InitializeAssembly(Assembly.GetExecutingAssembly());
        }

        public void RegisterTypes(IContainerRegistry containerRegistry)
        {
            containerRegistry.RegisterAssembly(Assembly.GetExecutingAssembly());

            if (!containerRegistry.IsRegistered<IControlCard>())
            {
                containerRegistry.RegisterSingleton<IControlCard, AdtechControlCard>();//注册众为兴控制卡到IOC容器中
            }
        }
    }
}
