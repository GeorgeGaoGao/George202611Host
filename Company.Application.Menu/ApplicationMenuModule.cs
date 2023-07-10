using Company.Application.Menu.Views;
using Company.Application.Share.Prism;
using Company.Core.Extension;
using Company.Core.Ioc;
using Prism.Ioc;
using Prism.Modularity;
using Prism.Regions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Company.Application.Menu
{
    [Module(ModuleName = ModuleNames.ApplicationMenuModule, OnDemand = true)]   
    public class ApplicationMenuModule : IModule
    {
        public void OnInitialized(IContainerProvider containerProvider)
        {
            containerProvider.InitializeAssembly(Assembly.GetExecutingAssembly());
            //containerProvider.Resolve<IRegionManager>().RegisterViewWithRegion<MenuView>(RegionNames.MenuRegion);
            PrismProvider.RegionManager.RegisterViewWithRegion<MenuView>(RegionNames.MenuRegion);
        }

        public void RegisterTypes(IContainerRegistry containerRegistry)
        {
            containerRegistry.RegisterAssembly(Assembly.GetExecutingAssembly());
            //containerRegistry.RegisterForNavigation<MenuView>();
        }
    }
}
