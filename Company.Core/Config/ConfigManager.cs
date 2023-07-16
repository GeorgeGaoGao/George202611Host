using Company.Core.Helper;
using Company.Core.Ioc;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Company.Core.Config
{
    [ExposedService(Lifetime.Singleton,typeof(IConfigManager))]
    public class ConfigManager : IConfigManager
    {
        private const string root = "Config";
        private string GetFullPath(ValueType key)
        {
            return Path.Combine(root, key.GetType().FullName + "." +key.ToString() + ".json");
        }

        /// <summary>
        /// 读配置文件
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="key"></param>
        /// <returns></returns>
        public T Read<T>(ValueType key)
        {
            string filename = GetFullPath(key);
            return JsonHelper.Load<T>(filename);
        }

        /// <summary>
        /// 写配置文件
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="key"></param>
        /// <param name="value"></param>
        public void Write<T>(ValueType key, T value)
        {
            Assert.NotNull(key);
            Assert.NotNull(value);
            Directory.CreateDirectory(root);
            string filename = GetFullPath(key);
            JsonHelper.Save(value, filename, true);
        }
    }
}
