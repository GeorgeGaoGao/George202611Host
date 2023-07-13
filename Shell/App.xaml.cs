using Company.Application.Share.Prism;
using Company.Core;
using Company.Logger;
using Prism.Ioc;
using Prism.Modularity;
using Prism.Unity;
using Shell.Views;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace Shell
{
    /// <summary>
    /// App.xaml 的交互逻辑
    /// </summary>
    public partial class App : PrismApplication
    {
        public App()
        {
            //程序域异常
            AppDomain.CurrentDomain.UnhandledException += (s, e) =>
            {
                Logs.LogError((Exception)(e.ExceptionObject));
            };

            //应用程序异常
            Current.DispatcherUnhandledException += (s, e) =>
            {
                Logs.LogError(e.Exception);
            };

            //多线程异常
            TaskScheduler.UnobservedTaskException += (s, e) =>
            {
                Logs.LogError(e.Exception);
            };
        }

        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            Logs.LogInfo("启动应用程序");
        }

        protected override void OnExit(ExitEventArgs e)
        {
            base.OnExit(e);

            Logs.LogInfo("关闭应用程序");
        }

        protected override Window CreateShell()
        {
            return new MainWindow();
        }

        protected override void RegisterTypes(IContainerRegistry containerRegistry)
        {
            
        }

        protected override void ConfigureModuleCatalog(IModuleCatalog moduleCatalog)
        {
            base.ConfigureModuleCatalog(moduleCatalog);

            moduleCatalog.AddModule<CoreModule>();
        }

        protected override IModuleCatalog CreateModuleCatalog()
        {
            return new DirectoryModuleCatalog() { ModulePath = ModuleNames.ModulePath};//配置本地模块目录
        }
    }
}
