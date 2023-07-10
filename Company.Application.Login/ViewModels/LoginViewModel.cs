using Company.Application.Share.Events;
using Company.Application.Share.Model;
using Company.Core.Dialog;
using Company.Core.Ioc;
using Prism.Commands;
using Prism.Mvvm;
using ReactiveUI;
using ReactiveUI.Fody.Helpers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Company.Application.Login.ViewModels
{
    public class LoginViewModel : ReactiveObject
    {
        [Reactive]
        public CurrentUser CurrentUser { get; set; } = new CurrentUser() { UserName = "admin", Password = "12345678" };

        public DelegateCommand LoginCommand => new DelegateCommand(() =>
        {
            if(string.IsNullOrEmpty(CurrentUser.UserName)|| string.IsNullOrEmpty(CurrentUser.Password))
            {
                return;
            }

            if (CurrentUser.UserName == "admin" && CurrentUser.Password == "12345678")
            {
                //当用户登录成功后给出通知或触发一个事件
                PrismProvider.EventAggregator.GetEvent<LoginSuccessEvent>().Publish(CurrentUser);
            }
            else
            {
                PopupBox.Show("用户名或密码错误");
            }

        });
    }
}
