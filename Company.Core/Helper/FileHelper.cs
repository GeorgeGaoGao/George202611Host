using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Company.Core.Helper
{
    /// <summary>
    /// 文件帮助 类
    /// </summary>
    public static class FileHelper
    {
        /// <summary>
        /// 以字节方式读取文件内容
        /// </summary>
        /// <param name="path"></param>
        /// <returns></returns>
        /// <exception cref="Exception"></exception>
        public static byte[] Load(string path)
        {
            if(File.Exists(path))
            {
                return File.ReadAllBytes(path);
            }

            throw new Exception($"{path}不存在");
        }
    }
}
