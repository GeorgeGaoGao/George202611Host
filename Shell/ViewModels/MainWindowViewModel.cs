using Company.Application.Share.Events;
using Company.Application.Share.Model;
using Company.Application.Share.Prism;
using Company.Core.Ioc;
using Prism.Commands;
using Prism.Events;
using Prism.Modularity;
using Prism.Mvvm;
using Prism.Regions;
using System;
using System.CodeDom;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;

namespace Shell.ViewModels
{
    internal class MainWindowViewModel : BindableBase
    {
        public ICommand LoadedCommand { get; }
        public IModuleManager ModuleManager { get; }
        public IRegionManager RegionManager { get; }
        public MainWindowViewModel(IModuleManager moduleManager,IRegionManager regionManager)
        {
            ModuleManager = moduleManager;
            RegionManager = regionManager;
            LoadedCommand = new DelegateCommand(Loaded);
        }

        private void Loaded()
        {
            IRegion mainRegion = PrismProvider.RegionManager.Regions[RegionNames.MainRegion];
            mainRegion.NavigationService.Navigated += NavigationService_Navigated;

            //第一步，加载Login模块
            PrismProvider.ModuleManager.LoadModule(ModuleNames.ApplicationLoginModule);
            //第二步，导航Login区域
            PrismProvider.RegionManager.RequestNavigate(RegionNames.MainRegion, ViewNames.LoginView);

            //订阅用户登录成功事件
            PrismProvider.EventAggregator.GetEvent<LoginSuccessEvent>().Subscribe(OnLogined, ThreadOption.UIThread);
        }

        private void OnLogined(CurrentUser user)
        {
            //加载主界面
            PrismProvider.ModuleManager.LoadModule(ModuleNames.ApplicatoinMainModule);
            //导航到主区域
            PrismProvider.RegionManager.RequestNavigate(RegionNames.MainRegion, ViewNames.MainView);

        }

        private Window MainWindow { get; set; }  = Application.Current.MainWindow;

        //当主区域导航时
        private void NavigationService_Navigated(object sender, RegionNavigationEventArgs e)
        {
            switch (e.Uri.OriginalString)
            {
                case ViewNames.LoginView:
                    //MainWindow.ResizeMode = ResizeMode.NoResize;
                    //MainWindow.SizeToContent = SizeToContent.WidthAndHeight;
                    //MainWindow.WindowState = WindowState.Normal;

                    //MainWindow.Width = 600;
                    //MainWindow.Height = 350;
                    //MainWindow.WindowStyle = WindowStyle.None;
                    break;

                case ViewNames.MainView:
                    MainWindow.Width = 1920;
                    MainWindow.Height = 1080;
                    MainWindow.ResizeMode = ResizeMode.CanResize;
                    MainWindow.SizeToContent = SizeToContent.Manual;
                    MainWindow.WindowState = WindowState.Maximized;
                    MainWindow.WindowStyle = WindowStyle.SingleBorderWindow;
                    break;
                default:
                    break;
            }
        }

        private string title = "重庆教主上位机开发VIP课程";
        public string Title
        {
            get { return title; }
            set { title = value; RaisePropertyChanged(); }
        }

    }
}
