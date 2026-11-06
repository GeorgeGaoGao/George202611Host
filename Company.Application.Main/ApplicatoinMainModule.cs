using Company.Application.Main.Views;
using Company.Application.Share.Prism;
using Prism.Ioc;
using Prism.Modularity;
using Prism.Regions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Company.Application.Main
{
    [Module(ModuleName = ModuleNames.ApplicatoinMainModule,OnDemand = true)]
    [ModuleDependency(ModuleNames.ApplicationMenuModule)]
    [ModuleDependency(ModuleNames.ApplicationImageModule)]
    public class ApplicatoinMainModule : IModule
    {
        public void OnInitialized(IContainerProvider containerProvider)
        {
            containerProvider.Resolve<IRegionManager>().RegisterViewWithRegion<MainView>(RegionNames.MainRegion) ;
            containerProvider.Resolve<IRegionManager>().RegisterViewWithRegion<PrimaryView>(RegionNames.PrimaryRegion);
        }

        public void RegisterTypes(IContainerRegistry containerRegistry)
        {
            containerRegistry.RegisterForNavigation<MainView>();
        }
    }
}
