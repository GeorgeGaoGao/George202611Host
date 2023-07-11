using Company.Application.Initialize.Services;
using Company.Application.Share.Prism;
using Company.Core.Ioc;
using Prism.Commands;
using ReactiveUI;
using ReactiveUI.Fody.Helpers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace Company.Application.Initialize.ViewModels
{
    internal class InitializeViewModel : ReactiveObject
    {
        [Reactive]
        public string Message { get; set; }

        private HardwareLifetimeManager Manager { get; set; }

        public ICommand LoadedCommand { get; }
        public InitializeViewModel(HardwareLifetimeManager manager)
        {
            Manager = manager;

            LoadedCommand = ReactiveCommand.Create(Init);

            //LoadedCommand = new DelegateCommand(Init);
        }

        /// <summary>
        /// 异步方法
        /// </summary>
        private async void Init()
        {
            if(!Manager.IsInitialized)
            {
                Message = "正在初始化所有硬件...";
                var result = await Manager.InitAsync();//等待
                if(!result.Success)
                {
                    Message = result.Message;
                    return;
                }
            }

            Message = "硬件初始化完成";

            //加载主界面
            await Task.Delay(100).ContinueWith(p =>
            {
                PrismProvider.Dispatcher.Invoke(() =>
                {
                    //加载主界面
                    PrismProvider.ModuleManager.LoadModule(ModuleNames.ApplicatoinMainModule);
                    //导航到主区域
                    PrismProvider.RegionManager.RequestNavigate(RegionNames.MainRegion, ViewNames.MainView);
                });
               
            });

        }
    }
}
