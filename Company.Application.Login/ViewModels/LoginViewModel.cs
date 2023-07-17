using Company.Application.Share.Events;
using Company.Application.Share.Model;
using Company.Core.Cache;
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
        private ICacheManager CacheManager { get; }
        public LoginViewModel(ICacheManager cacheManager)
        {
            CacheManager = cacheManager;

            LoadUserCache();

            //是否自动登录 

            Task.Delay(1500).ContinueWith(t =>
            {
                if(IsAutoLogin)
                {
                    LoginCommand.Execute();
                }
            });
        }

       

        [Reactive]
        public bool IsRemember { get; set; }
        [Reactive]
        public bool IsAutoLogin { get; set; }

        [Reactive]
        public CurrentUser CurrentUser { get; set; } = new CurrentUser();

        public DelegateCommand LoginCommand => new DelegateCommand(() =>
        {
            if(string.IsNullOrEmpty(CurrentUser.UserName)|| string.IsNullOrEmpty(CurrentUser.Password))
            {
                return;
            }

            if(IsRemember)
            {
                CacheManager.Set(CacheKey.User, CurrentUser);
            }
            else
            {
                CacheManager.Delete(CacheKey.User);
            }

            CacheManager.Set(CacheKey.IsRemember, IsRemember);
            CacheManager.Set(CacheKey.IsAutoLogin, IsAutoLogin);


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


        /// <summary>
        /// 获取用户缓存
        /// </summary>
        private void LoadUserCache()
        {
            if(CacheManager.Get(CacheKey.User,out CurrentUser user))
            {
                CurrentUser.UserName= user.UserName;
                CurrentUser.Password= user.Password;
            }

            if(CacheManager.Get(CacheKey.IsRemember, out bool isRemember))
            {
                IsRemember = isRemember;
            }

            if (CacheManager.Get(CacheKey.IsAutoLogin, out bool isAutoLogin))
            {
                IsAutoLogin = isAutoLogin;
            }
        }
    }
}
