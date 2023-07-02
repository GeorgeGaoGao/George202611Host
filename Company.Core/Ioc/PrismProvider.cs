using Company.Core.Language;
using Prism.Events;
using Prism.Ioc;
using Prism.Modularity;
using Prism.Regions;
using Prism.Services.Dialogs;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Company.Core.Ioc
{
    [ExposedServiceAttribute(Lifetime.Singleton,AutoInitialize =true)]
    public sealed class PrismProvider
    {

        public PrismProvider(
            ILanguageManager language,
            IContainerExtension container,
            IRegionManager regionManager,
            IDialogService dialogService,
            IEventAggregator eventAggregator,
            IModuleManager moduleManager)
        {
            LanguageManager = language;
            Container = container;
            RegionManager = regionManager;
            DialogService = dialogService;
            EventAggregator = eventAggregator;
            ModuleManager = moduleManager; 
        }

        /// <summary>
        /// 语言助手
        /// </summary>
        public static ILanguageManager LanguageManager { get; private set; }

        /// <summary>
        /// 容器
        /// </summary>
        public static IContainerExtension Container { get; private set; }

        /// <summary>
        /// 区域管理器接口
        /// </summary>
        public static IRegionManager RegionManager { get; private set; }

        /// <summary>
        /// 对话框管理器
        /// </summary>
        public static IDialogService DialogService { get; private set; }

        /// <summary>
        /// 事件聚合器
        /// </summary>
        public static IEventAggregator EventAggregator { get; private set; }

        /// <summary>
        /// 模块管理器
        /// </summary>
        public static IModuleManager ModuleManager { get; private set; }

    }
}
