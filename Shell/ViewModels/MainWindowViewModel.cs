using Prism.Modularity;
using Prism.Mvvm;
using Prism.Regions;
using System;
using System.CodeDom;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Shell.ViewModels
{
    internal class MainWindowViewModel : BindableBase
    {
        public IModuleManager ModuleManager { get; }
        public IRegionManager RegionManager { get; }
        public MainWindowViewModel(IModuleManager moduleManager,IRegionManager regionManager)
        {
            ModuleManager = moduleManager;
            RegionManager = regionManager;
        }
        private string title = "重庆教主上位机开发VIP课程";
        public string Title
        {
            get { return title; }
            set { title = value; RaisePropertyChanged(); }
        }

    }
}
