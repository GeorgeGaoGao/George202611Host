using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace Company.Core.Helper
{
    /// <summary>
    /// 断言类型，判断参数或对象是否为空
    /// </summary>
    public static class Assert
    {
        public static void NotNull<T>(T obj, [CallerMemberName] string memberName = null)
        {
            if (obj == null)
            {
                throw new Exception($"断言错误:{memberName}方法中的{typeof(T)}不可为空！");
            }
        }
    }
}
