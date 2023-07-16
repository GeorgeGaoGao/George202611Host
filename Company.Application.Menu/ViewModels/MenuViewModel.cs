using Company.Application.Share.Prism;
using Company.Core.Ioc;
using Prism.Commands;
using Prism.Mvvm;
using Prism.Services.Dialogs;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace Company.Application.Menu.ViewModels
{
    internal class MenuViewModel : BindableBase
    {
        public ICommand SystemConfigCommand { get; }

        public MenuViewModel()
        {
            SystemConfigCommand = new DelegateCommand(SystemConfig);
        }

        private void SystemConfig()
        {
            PrismProvider.DialogService.ShowDialog(ViewNames.ConfigView, Callback);
        }

        private void Callback(IDialogResult result)
        {
            //todo...
        }
    }
}
