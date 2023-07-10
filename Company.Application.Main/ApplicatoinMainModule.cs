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
    public class ApplicatoinMainModule : IModule
    {
        public void OnInitialized(IContainerProvider containerProvider)
        {
            containerProvider.Resolve<IRegionManager>().RegisterViewWithRegion<MainView>(RegionNames.MainRegion) ;
        }

        public void RegisterTypes(IContainerRegistry containerRegistry)
        {
            containerRegistry.RegisterForNavigation<MainView>();
        }
    }
}
