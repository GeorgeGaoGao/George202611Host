using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Company.Core.Helper
{
    /// <summary>
    /// Json文件的序列化和反序列化帮助类
    /// </summary>
    public static class JsonHelper
    {
        /// <summary>
        /// 加载某个JSON文件并返回指定的类型实例
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="fileName"></param>
        /// <returns></returns>
        public static T Load<T>(string fileName)
        {
            if(!File.Exists(fileName))
            {
                return default(T);
            }

            string content = File.ReadAllText(fileName);
            return Deserialize<T>(content);
        }

        public static T Deserialize<T>(string content)
        {
            return JsonConvert.DeserializeObject<T>(content);
        }

        /// <summary>
        /// 将指定的类型实例保存为JSON文件
        /// </summary>
        /// <param name="obj"></param>
        /// <param name="fileName"></param>
        /// <param name="indented"></param>
        public static void Save(object obj, string fileName,bool indented = false) 
        {
            string content = Serialize(obj, indented);
        }

        private static string Serialize(object obj, bool indented)
        {
            Formatting formatting = indented ? Formatting.Indented : Formatting.None;
            return JsonConvert.SerializeObject(obj, formatting);
        }
    }
}
