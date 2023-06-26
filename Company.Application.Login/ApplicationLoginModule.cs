using Company.Application.Login.Views;
using Company.Application.Share.Prism;
using Prism.Ioc;
using Prism.Modularity;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Company.Application.Login
{
    /// <summary>
    /// 登录模块 - 按需延迟加载
    /// </summary>
    [Module(ModuleName = ModuleNames.ApplicationLoginModule,OnDemand = true)]
    public class ApplicationLoginModule : IModule
    {
        //先注册
        public void RegisterTypes(IContainerRegistry containerRegistry)
        {
            containerRegistry.RegisterForNavigation<LoginView>();
        }

        //后初始化
        public void OnInitialized(IContainerProvider containerProvider)
        {
            
        }

        
    }
}
