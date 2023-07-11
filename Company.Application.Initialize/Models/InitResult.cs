using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Company.Application.Initialize.Models
{
    /// <summary>
    /// 硬件加载返回结果
    /// </summary>
    public struct InitResult
    {
        public string Message { get; set; }
        public bool Success { get; set; }
    }
}
