using Company.Application.Share.Model;
using Prism.Events;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Company.Application.Share.Events
{
    /// <summary>
    /// 用户登录成功时
    /// </summary>
    public class LoginSuccessEvent : PubSubEvent<CurrentUser>
    {
    }
}
