using Company.Application.Config.Services;
using Company.Application.Share.Config;
using Company.Core.Ioc;
using ReactiveUI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace Company.Application.Config.ViewModels
{
    internal class ConfigViewModel : DialogViewModelBase
    {
        public SystemConfigManager SystemConfigManager { get; }
        public SystemConfigProvider SystemConfigProvider { get; }

        public ICommand OKCommand { get; }
        public ConfigViewModel(SystemConfigManager systemConfigManager, SystemConfigProvider systemConfigProvider)
        {
            SystemConfigManager = systemConfigManager;
            SystemConfigProvider = systemConfigProvider;
            OKCommand = ReactiveCommand.Create(Submit);
        }

        private void Submit()
        {
            SystemConfigManager.Save();//保存参数到本机JSON
            SystemConfigProvider.Invoke();//通知硬件重新初始化相关参数
            CloseDialog(Prism.Services.Dialogs.ButtonResult.OK);
        }
    }
}
