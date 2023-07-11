using Company.Application.Initialize.Views;
using Company.Application.Share.Prism;
using Company.Core.Extension;
using Prism.Ioc;
using Prism.Modularity;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Company.Application.Initialize
{
    /// <summary>
    /// 硬件初始化模块
    /// </summary>
    [Module(ModuleName = ModuleNames.ApplicationInitializeModule, OnDemand = true)]
    public class ApplicationInitializeModule : IModule
    {
        public void OnInitialized(IContainerProvider containerProvider)
        {
            containerProvider.InitializeAssembly(Assembly.GetExecutingAssembly());
        }

        public void RegisterTypes(IContainerRegistry containerRegistry)
        {
            containerRegistry.RegisterAssembly(Assembly.GetExecutingAssembly());

            containerRegistry.RegisterForNavigation<InitializeView>();
        }
    }
}
