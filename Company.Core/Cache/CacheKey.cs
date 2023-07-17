using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Company.Core.Cache
{
    /// <summary>
    /// 用枚举区分缓存
    /// </summary>
    public enum CacheKey
    {
        /// <summary>
        /// 当前用户
        /// </summary>
        User,

        /// <summary>
        /// 是否自动登录 
        /// </summary>
        IsAutoLogin,

        /// <summary>
        /// 是否记住密码
        /// </summary>
        IsRemember,
    }
}
